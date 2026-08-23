ls -l /proc/$$/ns/mnt
sudo unshare -m bash

# inside new bash shell
ls -l /proc/$$/ns/mnt
cat /proc/$$/mountinfo | grep -E '(/proc |/tmp|/vda2)'