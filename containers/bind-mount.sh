mkdir -p /home/${USER}/{wrk1,wrk2}
touch /home/${USER}/wrk1/WORK_FILE.txt
touch /home/${USER}/wrk2/HIDDEN_FILE.txt

ls /home/${USER}/wrk2
sudo mount --bind /home/${USER}/wrk1/ /home/${USER}/wrk2/
ls /home/${USER}/wrk2

sudo umount /home/${USER}/wrk2
ls /home/${USER}/wrk2