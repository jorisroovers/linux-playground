# Signals

Compilation:

```sh
mkdir bin

gcc -std=c99 signals/signals.c -o bin/signals
gcc -std=c99 signals/kill.c -o bin/kill
```

Handling signals:

```sh
# Run program in the background (makes it easier to manipulate in single terminal)
bin/signals &

# Try CTRL+C (=SIGINT = interrupt) on the bin/signals
# Also try different signals:
kill -SIGINT `pgrep signals`  # (keyboard) interrupt process
kill -SIGTERM `pgrep signals` # terminate process
kill -SIGKILL `pgrep signals` # force kill process
kill -SIGSTOP `pgrep signals` # pause process
kill -SIGCONT `pgrep signals` # resume process
# resize window
```

Sending signals:

```sh
# Start signals program in the background:
bin/signals &

# Send signal to process
bin/kill `pgrep signals` 15 # 15 = SIGTERM
```