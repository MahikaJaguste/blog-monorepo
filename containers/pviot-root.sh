# running pivot_root requires root capability
sudo -i
# prepare new_root and oldroot is a subdirectory inside new_root
mkdir -p /home/${USER}/new_rootfs/{bin,oldroot}
# to be able to run utility commands when root is mounted on new_rootfs
cp /bin/busybox /home/${USER}/new_rootfs/bin

# run bash shell program in new mount namespace
unshare -m bash

# ...inside new bash shell
# observe existing mount objects in new mount namespace
cat /proc/self/mountinfo | grep -E '(/proc |/tmp|/vda2|rootfs|/oldroot |/oldroot/proc )'
	
# bind mount new_rootfs on itself
mount --bind /home/${USER}/new_rootfs/ /home/${USER}/new_rootfs/
	
# pivot root
pivot_root /home/${USER}/new_rootfs/ /home/${USER}/new_rootfs/oldroot
cd /

# mount proc filesystem at /proc location
busybox mkdir -p proc
busybox mount -t proc proc /proc

# clean up oldroot
busybox cat /proc/self/mountinfo \
    | busybox awk '{print $5}' \
    | busybox grep '^/oldroot' \
    | busybox sort -r \
    | busybox xargs -r -n1 busybox umount -l
busybox umount /proc
