while pgrep kqueue_fd_demo >/dev/null; do
    sample $(pgrep kqueue_fd_demo) 1 >> all.txt
done