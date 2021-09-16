# Hard linking directories
Use these files with caution; most tools (including fsck) are fairly incapable
of dealing with directory cycles which these executables will let you make.

Below is the original `README` a that I wrote in November of 2016, much of this
information is not necessarily true and are overly superstitious etc., but I'm
preserving it for historical reasons, and because the degree of alarm in it is
somewhat appropriate when creating directory hard links.

> This directory contains executables that do the very dangerous thing of hard
> linking anything to something else.  While doing this the following rules are
> very important to maintain filesystem integrity:
> 1. The file system must be journaled HFS+.
> 2. The parent directories of the source and destination must be different.
> 3. The source’s parent must not be the root directory.
> 4. The destination must not be in the root directory.
> 5. The destination must not be a descendent of the source.
> 6. The destination must not have any ancestor that’s a directory hard link.
>
> Otherwise it is relatively likely that the filesystem could become corrupt or
> that other things could be broken.
>
> See the following URL for more information:
> http://stackoverflow.com/questions/80875/what-is-the-unix-command-to-create-a-hardlink-to-a-directory-in-os-x
>
> It is important to keep a log of hard linked directories made and is also
> essential to unlink them using hunlink.  The log of hardlinked files is at
> /private/var/root/bin/hard_links/LOGFILE
>
> Compiling and using the programs is very dangerous.  Do with caution.
