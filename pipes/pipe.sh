#!/bin/sh

mknod -m=rw dirinfo p

ls -la > dirinfo &
grep pipe dirinfo
