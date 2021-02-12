# slstatus - suckless status
My fork of suckless's [slstatus](https://tools.suckless.org/slstatus/) for the
[dwm](https://dwm.suckless.org/) title bar.

Changes from the original program:
* Updated `ram_used` in `components/ram.c` to match the definition in
    `free(1)`, i.e.
    ```
    used = total - free - buffers - cache,
    ```
    where `total = MemTotal`, `free = MemFree`, `buffers = Buffers`, and
    `cache = Cached + SReclaimable` in `/proc/meminfo` (original does not
    include `SReclaimable`)
* Added a function `available_updates` that checks for package updates using
    the `checkupdates` command from pacman-contrib

