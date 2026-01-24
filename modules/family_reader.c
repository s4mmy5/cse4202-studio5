/*
 * This kobject reveals family history on a partical PID.
 */

#include <linux/init.h>
#include <linux/kobject.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/string.h>
#include <linux/sysfs.h>
#include <linux/pid.h>
#include <linux/types.h>
#include <linux/sched/signal.h>

static int curr_pid;
static int task_exp; // task explorer

static inline char *is_enabled(int bool) {
  return bool ? "TRUE" : "FALSE";
}

/*
 * The "task_exp" file we can use to trigger functionality
 */
static ssize_t task_exp_show(struct kobject *kobj, struct kobj_attribute *attr,
                        char *buf) {
  return sprintf(buf, "Enabled: %s\n", is_enabled(task_exp));
}

static ssize_t task_exp_store(struct kobject *kobj, struct kobj_attribute *attr,
                         const char *buf, size_t count) {
  int ret, old_task_exp;
  struct task_struct *curr_task;

  old_task_exp = task_exp;
  ret = kstrtoint(buf, 10, &task_exp);

  printk("task_exp value being updated (OLD=%s, NEW=%s)\n", is_enabled(old_task_exp), is_enabled(task_exp));
  if (ret < 0)
    return ret;

  printk("%10s|%10s|%30s\n", "PID", "PPID", "Command");
  if (task_exp) {
    for_each_process(curr_task) {
        printk("%10d|%10d|%30s\n", curr_task->pid, curr_task->real_parent->pid, curr_task->comm);
    }
  }

  return count;
}

/*
 * The "pid" file where a static variable is read from and written to.
 */
static ssize_t pid_show(struct kobject *kobj, struct kobj_attribute *attr,
                        char *buf) {
  return sprintf(buf, "%d\n", curr_pid);
}

static ssize_t pid_store(struct kobject *kobj, struct kobj_attribute *attr,
                         const char *buf, size_t count) {
  int ret, old_pid;
  struct pid* real_pid;
  struct task_struct* pid_task;

  old_pid = curr_pid;
  ret = kstrtoint(buf, 10, &curr_pid);
  printk("pid value being updated (OLD=%d, NEW=%d)\n", old_pid, curr_pid);
  if (ret < 0)
    return ret;

  if (!(real_pid = find_vpid(curr_pid))) {
    printk("Failed to find real_pid\n");
    goto err;
  }

  if (!(pid_task = get_pid_task(real_pid, PIDTYPE_PID))) {
    printk("Failed to find task_struct\n");
    goto err;
  }

  do {
    printk("PID: %d\n", pid_task->pid);
    printk("Command: %s\n", pid_task->comm);
    printk("Start time: %llu\n", pid_task->start_time);
    printk("Number of Voluntary Context Switches: %lu\n", pid_task->nvcsw);
    printk("Number of InVoluntary Context Switches: %lu\n", pid_task->nivcsw);
  } while ((pid_task = pid_task->real_parent)->pid > 0);

err:
  return count;
}

/* Sysfs attributes cannot be world-writable. */
static struct kobj_attribute pid_attribute =
    __ATTR(curr_pid, 0664, pid_show, pid_store);

static struct kobj_attribute task_exp_attribute =
    __ATTR(task_exp, 0664, task_exp_show, task_exp_store);

/*
 * Create a group of attributes so that we can create and destroy them all
 * at once.
 */
static struct attribute *attrs[] = {
    &pid_attribute.attr, &task_exp_attribute.attr,
    NULL, /* need to NULL terminate the list of attributes */
};

/*
 * An unnamed attribute group will put all of the attributes directly in
 * the kobject directory.  If we specify a name, a subdirectory will be
 * created for the attributes with the directory being the name of the
 * attribute group.
 */
static struct attribute_group attr_group = {
    .attrs = attrs,
};

static struct kobject *example_kobj;

static int __init m_init(void) {
  int retval;

  /*
   * Create a simple kobject with the name of "example_kobj",
   * located under /sys/kernel/
   *
   * As this is a simple directory, no uevent will be sent to
   * userspace.  That is why this function should not be used for
   * any type of dynamic kobjects, where the name and number are
   * not known ahead of time.
   */
  example_kobj = kobject_create_and_add("fam_reader", kernel_kobj);
  if (!example_kobj)
    return -ENOMEM;

  /* Create the files associated with this kobject */
  retval = sysfs_create_group(example_kobj, &attr_group);
  if (retval)
    kobject_put(example_kobj);

  return retval;
}

static void __exit m_exit(void) { kobject_put(example_kobj); }

module_init(m_init);
module_exit(m_exit);
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Jonathan Rodriguez Gomez <j.rodriguezgomez@wustl.edu>");
