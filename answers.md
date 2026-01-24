# Studio 5: Processes

## Base Exercises
1. Contributors:
   - Jonathan Rodriguez Gomez
   
2. Simple Fork:
```
Parent: before fork
Parent: after fork
Child: (PID=31964, PPID=31963)
Parent: the child is dead (child PID=31964)
```

3. tree_fork.c:

```
sammy@mikey:~ $ ./tree_fork 4 > out
sammy@mikey:~ $ cat out 
My generation is 0. (PID=8981, PPID=1312)
My generation is 1. (PID=8982, PPID=8981)
My generation is 1. (PID=8983, PPID=8981)
My generation is 2. (PID=8985, PPID=8983)
My generation is 2. (PID=8986, PPID=8983)
My generation is 2. (PID=8988, PPID=8982)
My generation is 3. (PID=8989, PPID=8985)
My generation is 2. (PID=8984, PPID=1)
My generation is 3. (PID=8987, PPID=1)
My generation is 3. (PID=8994, PPID=1)
My generation is 3. (PID=8991, PPID=1)
My generation is 3. (PID=8998, PPID=1)
My generation is 3. (PID=8992, PPID=8986)
My generation is 3. (PID=8996, PPID=1)
My generation is 3. (PID=8990, PPID=8986)
sammy@mikey:~ $ wc -l out
15 out
```

4. kobject_example:
```
root@mikey:/sys/kernel/kobject_example# cat foo
0
root@mikey:/sys/kernel/kobject_example# echo 42 > foo
root@mikey:/sys/kernel/kobject_example# cat foo
42
root@mikey:/sys/kernel/kobject_example# dmesg
[  170.868408] kobject_example: loading out-of-tree module taints kernel.
[  293.433267] foo value being updated (OLD=0, NEW=42)
root@mikey:/sys/kernel/kobject_example#
```

5. family_reader module:
```
[ 1834.667364] family_reader: loading out-of-tree module taints kernel.
[ 1866.950214] pid value being updated (OLD=0, NEW=21458)
[ 1866.950237] PID: 21458
[ 1866.950253] Command: su
[ 1866.950269] PID: 21265
[ 1866.950285] Command: bash
[ 1866.950300] PID: 21261
[ 1866.950315] Command: sshd
[ 1866.950331] PID: 21245
[ 1866.950346] Command: sshd
[ 1866.950362] PID: 484
[ 1866.950377] Command: sshd
[ 1866.950392] PID: 1
[ 1866.950407] Command: systemd
```

## Enrichment Exercises

6. Exploring task_struct:
```
[ 2539.900160] pid value being updated (OLD=28922, NEW=21501)
[ 2539.900183] PID: 21501
[ 2539.900200] Command: bash
[ 2539.900216] Start time: 1830047312291
[ 2539.900232] Number of Voluntary Context Switches: 512
[ 2539.900247] Number of InVoluntary Context Switches: 12
[ 2539.900265] PID: 21458
[ 2539.900281] Command: su
[ 2539.900296] Start time: 1826245185502
[ 2539.900312] Number of Voluntary Context Switches: 10
[ 2539.900327] Number of InVoluntary Context Switches: 37
[ 2539.900343] PID: 21265
[ 2539.900358] Command: bash
[ 2539.900375] Start time: 1810735597549
[ 2539.900396] Number of Voluntary Context Switches: 64
[ 2539.900415] Number of InVoluntary Context Switches: 15
[ 2539.900430] PID: 21261
[ 2539.900446] Command: sshd
[ 2539.900461] Start time: 1810482160271
[ 2539.900476] Number of Voluntary Context Switches: 1259
[ 2539.900492] Number of InVoluntary Context Switches: 330
[ 2539.900507] PID: 21245
[ 2539.900522] Command: sshd
[ 2539.900537] Start time: 1809644562049
[ 2539.900555] Number of Voluntary Context Switches: 18
[ 2539.900570] Number of InVoluntary Context Switches: 17
[ 2539.900585] PID: 484
[ 2539.900601] Command: sshd
[ 2539.900616] Start time: 8464396049
[ 2539.900632] Number of Voluntary Context Switches: 21
[ 2539.900648] Number of InVoluntary Context Switches: 37
[ 2539.900664] PID: 1
[ 2539.900683] Command: systemd
[ 2539.900704] Start time: 0
[ 2539.900720] Number of Voluntary Context Switches: 1785
[ 2539.900735] Number of InVoluntary Context Switches: 1594
```

After looking we see a really interesting one nvcsw and nivcsw, which keep track of context switches. It is really interesting to see how interactive programs like the bash shell trigger a high amount of voluntary context switches while longer running programs will often see more involuntary context switches.

7. I used for_each_process to create a very barebones version of the top program, everytime you write to the sysfs entry it outputs a table of all running processes to the system log.

This is what it looks like:
```
[ 7371.216398]        PID|      PPID|                       Command
[ 7371.216418]          1|         0|                       systemd
[ 7371.216435]          2|         0|                      kthreadd
[ 7371.216452]          3|         2|                        rcu_gp
[ 7371.216468]          4|         2|                    rcu_par_gp
[ 7371.216487]          8|         2|                  mm_percpu_wq
[ 7371.216504]          9|         2|               rcu_tasks_kthre
[ 7371.216522]         10|         2|               rcu_tasks_rude_
[ 7371.216538]         11|         2|               rcu_tasks_trace
[ 7371.216555]         12|         2|                   ksoftirqd/0
[ 7371.216571]         13|         2|                   rcu_preempt
[ 7371.216587]         14|         2|                   migration/0
[ 7371.216606]         15|         2|                       cpuhp/0
[ 7371.216626]         16|         2|                       cpuhp/1
[ 7371.216642]         17|         2|                   migration/1
[ 7371.216658]         18|         2|                   ksoftirqd/1
[ 7371.216674]         21|         2|                       cpuhp/2
[ 7371.216690]         22|         2|                   migration/2
[ 7371.216706]         23|         2|                   ksoftirqd/2
[ 7371.216722]         26|         2|                       cpuhp/3
[ 7371.216740]         27|         2|                   migration/3
[ 7371.216757]         28|         2|                   ksoftirqd/3
[ 7371.216774]         31|         2|                     kdevtmpfs
[ 7371.216790]         32|         2|                         netns
[ 7371.216806]         36|         2|                       kauditd
[ 7371.216822]         37|         2|                    khungtaskd
[ 7371.216838]         38|         2|                    oom_reaper
[ 7371.216855]         39|         2|                     writeback
[ 7371.216877]         40|         2|                    kcompactd0
[ 7371.216893]         58|         2|                       kblockd
[ 7371.216910]         59|         2|                blkcg_punt_bio
[ 7371.216926]         60|         2|                     watchdogd
[ 7371.216942]         62|         2|                        rpciod
[ 7371.216958]         63|         2|                  kworker/u9:0
[ 7371.216974]         64|         2|                       xprtiod
[ 7371.216990]         65|         2|                       kswapd0
[ 7371.217007]         66|         2|                        nfsiod
[ 7371.217023]         67|         2|                      kthrotld
[ 7371.217040]         69|         2|                      iscsi_eh
[ 7371.217058]         70|         2|                 iscsi_destroy
[ 7371.217074]         73|         2|               DWC Notificatio
[ 7371.217091]         74|         2|                           uas
[ 7371.217107]         75|         2|                  vchiq-slot/0
[ 7371.217123]         76|         2|                  vchiq-recy/0
[ 7371.217139]         77|         2|                  vchiq-sync/0
[ 7371.217155]         78|         2|                  zswap-shrink
[ 7371.217180]         80|         2|                         sdhci
[ 7371.217200]         81|         2|                   irq/66-mmc0
[ 7371.217216]         83|         2|                  mmc_complete
[ 7371.217232]         86|         2|               jbd2/mmcblk0p2-
[ 7371.217248]         87|         2|               ext4-rsv-conver
[ 7371.217264]         88|         2|                 ipv6_addrconf
[ 7371.217281]        128|         1|               systemd-journal
[ 7371.217297]        155|         1|                 systemd-udevd
[ 7371.217313]        191|         2|                  vchiq-keep/0
[ 7371.217330]        192|         2|                          SMIO
[ 7371.217349]        201|         2|                    mmal-vchiq
[ 7371.217365]        206|         2|                    mmal-vchiq
[ 7371.217381]        207|         2|                    mmal-vchiq
[ 7371.217398]        208|         2|                    mmal-vchiq
[ 7371.217414]        245|         2|                      cfg80211
[ 7371.217430]        249|         2|               brcmf_wq/mmc1:0
[ 7371.217447]        252|         2|               brcmf_wdog/mmc1
[ 7371.217468]        275|         2|                   kworker/1:3
[ 7371.217489]        336|         1|                  avahi-daemon
[ 7371.217510]        337|         1|                          cron
[ 7371.217526]        341|         1|                   dbus-daemon
[ 7371.217542]        353|       336|                  avahi-daemon
[ 7371.217559]        380|         1|                      rsyslogd
[ 7371.217575]        386|         1|                systemd-logind
[ 7371.217591]        390|         1|                           thd
[ 7371.217608]        399|         1|                       udisksd
[ 7371.217624]        402|         1|                wpa_supplicant
[ 7371.217640]        449|         1|                         cupsd
[ 7371.217656]        455|         1|                          rngd
[ 7371.217675]        464|         1|                       lightdm
[ 7371.217691]        465|         1|                        dhcpcd
[ 7371.217707]        471|         1|                       polkitd
[ 7371.217723]        484|         1|                          sshd
[ 7371.217739]        487|       449|                          dbus
[ 7371.217755]        488|       449|                          dbus
[ 7371.217772]        489|       449|                          dbus
[ 7371.217791]        492|         1|                  cups-browsed
[ 7371.217807]        504|         1|                         login
[ 7371.217824]        518|         1|                wpa_supplicant
[ 7371.217840]        591|         1|                       systemd
[ 7371.217856]        593|       591|                      (sd-pam)
[ 7371.217872]        621|         1|                     hciattach
[ 7371.217888]        622|         2|                  kworker/u9:1
[ 7371.217905]        640|         1|                    bluetoothd
[ 7371.217921]        649|         2|                        cryptd
[ 7371.217937]        676|       591|                      pipewire
[ 7371.217953]        677|       591|                    pulseaudio
[ 7371.217970]        678|       504|                          bash
[ 7371.217986]        681|         1|                  rtkit-daemon
[ 7371.218002]        697|       591|                   dbus-daemon
[ 7371.218018]        699|         1|                     ssh-agent
[ 7371.218034]        701|       676|               pipewire-media-
[ 7371.218050]        708|         2|                      krfcommd
[ 7371.218066]       8032|         2|                  kworker/0:0H
[ 7371.218082]      13529|         2|                   kworker/1:0
[ 7371.218099]      21245|       484|                          sshd
[ 7371.218115]      21261|     21245|                          sshd
[ 7371.218131]      21265|     21261|                          bash
[ 7371.218147]      21280|         1|                     ssh-agent
[ 7371.218163]      21458|     21265|                            su
[ 7371.218179]      21501|     21458|                          bash
[ 7371.218195]       7101|         2|                   kworker/2:2
[ 7371.218211]       7471|         2|                  kworker/3:2H
[ 7371.218228]       9735|         2|                  kworker/u8:1
[ 7371.218244]      16589|         2|                  kworker/2:2H
[ 7371.218260]      30594|         2|                   kworker/0:2
[ 7371.218276]      31280|         2|                  kworker/1:0H
[ 7371.218293]      32165|         2|                   kworker/3:0
[ 7371.218309]       6048|         2|                   kworker/0:0
[ 7371.218325]       6379|         2|                  kworker/u8:4
[ 7371.218341]       7736|         1|               systemd-timesyn
[ 7371.218357]       8065|         2|                  kworker/3:1H
[ 7371.218373]       8744|         2|                  kworker/1:1H
[ 7371.218389]       9374|         2|                   kworker/3:1
[ 7371.218405]       9751|         2|                  kworker/0:2H
[ 7371.218421]       9810|         2|                  kworker/2:0H
[ 7371.218437]       9923|         2|                   kworker/2:0
[ 7371.218453]      11232|         2|                   kworker/0:1
[ 7371.218469]      11518|         2|                  kworker/3:0H
[ 7371.218486]      12287|         2|                   kworker/3:2
[ 7371.218502]      12887|         2|                   kworker/2:1
[ 7371.218518]      13625|         2|                  kworker/u8:0
[ 7371.218534]      13638|       464|                          Xorg
```
