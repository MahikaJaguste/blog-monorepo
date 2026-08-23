mkdir -p /home/${USER}/rootfs/{bin,proc}
cp /bin/busybox /home/${USER}/rootfs/bin
sudo mount -t proc proc /home/${USER}/rootfs/proc
sudo chroot /home/${USER}/rootfs /bin/busybox sh

# to access things outside our root, cd proc/1/root