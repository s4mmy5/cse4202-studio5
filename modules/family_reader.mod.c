#include <linux/module.h>
#define INCLUDE_VERMAGIC
#include <linux/build-salt.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif

static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0xb92a4e79, "module_layout" },
	{ 0xfbc57363, "kobject_put" },
	{ 0x18be14d8, "sysfs_create_group" },
	{ 0x20ae3040, "kobject_create_and_add" },
	{ 0xa191e9ba, "kernel_kobj" },
	{ 0x1d26d18, "get_pid_task" },
	{ 0x1e73a11b, "find_vpid" },
	{ 0x214ba01b, "init_task" },
	{ 0xc5850110, "printk" },
	{ 0x8c8569cb, "kstrtoint" },
	{ 0x3c3ff9fd, "sprintf" },
	{ 0xb1ad28e0, "__gnu_mcount_nc" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "210871C85FEB7013BD8B927");
