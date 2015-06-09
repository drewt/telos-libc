AUTOMAKE_OPTIONS = cygnus
INCLUDES = -I$(srcdir)/include $(NEWLIB_CFLAGS) $(CROSS_CFLAGS) $(TARGET_CFLAGS)
AM_CCASFLAGS = $(INCLUDES)
 
noinst_LIBRARIES = lib.a
 
if MAY_SUPPLY_SYSCALLS
extra_objs = _exit.o alarm.o aligned_alloc.o chdir.o clock.o close.o closedir.o dir.o dup.o dup2.o environ.o execve.o fcntl.o fork.o getpid.o gettimeofday.o ioctl.o isatty.o kill.o link.o lseek.o mkdir.o mknod.o mmap.o mount.o nanosleep.o open.o opendir.o pipe.o pread.o pwrite.o read.o readdir.o rename.o rmdir.o sbrk.o sched_yield.o sigaction.o signal.o sigprocmask.o sigqueue.o sigsuspend.o sigwait.o sleep.o stat.o timer.o times.o truncate.o umount.o unlink.o wait.o write.o
else
extra_objs =
endif
 
lib_a_SOURCES =
lib_a_LIBADD = $(extra_objs)
EXTRA_lib_a_SOURCES = _exit.c alarm.c aligned_alloc.c chdir.c clock.c close.c closedir.c dir.c dup.c dup2.c environ.c execve.c fcntl.c fork.c getpid.c gettimeofday.c ioctl.c isatty.c kill.c link.c lseek.c mkdir.c mknod.c mmap.c mount.c nanosleep.c open.c opendir.c pipe.c pread.c pwrite.c read.c readdir.c rename.c rmdir.c sbrk.c sched_yield.c sigaction.c signal.c sigprocmask.c sigqueue.c sigsuspend.c sigwait.c sleep.c stat.c timer.c times.c truncate.c umount.c unlink.c wait.c write.c crt0.s
lib_a_DEPENDENCIES = $(extra_objs)
lib_a_CCASFLAGS = $(AM_CCASFLAGS)
lib_a_CFLAGS = $(AM_CFLAGS)
 
if MAY_SUPPLY_SYSCALLS
all: crt0.o
endif

install-data-local:
	$(mkinstalldirs) $(DESTDIR)$(tooldir)/include/telos
 
ACLOCAL_AMFLAGS = -I ../../..
CONFIG_STATUS_DEPENDENCIES = $(newlib_basedir)/configure.host
