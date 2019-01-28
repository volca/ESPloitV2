Import("env")

# please keep $SOURCE variable, it will be replaced with a path to firmware

# Generic
env.Replace(
    UPLOADER="python esptool.py "
    UPLOADCMD="$UPLOADER $UPLOADERFLAGS $SOURCE"
)
