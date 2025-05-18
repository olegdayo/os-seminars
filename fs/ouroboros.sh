#!/bin/sh

touch file
ln -s file symlink
ln -s symlink symsymlink
rm file
mv symsymlink file
