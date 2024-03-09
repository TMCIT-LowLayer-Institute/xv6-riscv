#include "types.h"
#include "param.h"
#include "memlayout.h"
#include "riscv.h"
#include "defs.h"

volatile static int started = 0;

// start() jumps here in supervisor mode on all CPUs.
  int
main()
{
  if(cpuid() == 0){
    consoleinit();
    printfinit();
    printf("\n");
    printf("xv6 kernel is booting\n");
    printf("    ________  ________ _____ _____      _                   _                                _____          _   _ _         _       \n");
    printf("   |_   _|  \\/  /  __ \\_   _|_   _|    | |                 | |                              |_   _|        | | (_) |       | |      \n");
    printf("     | | | .  . | /  \\/ | |   | |______| |     _____      _| |     __ _ _   _  ___ _ __ ______| | _ __  ___| |_ _| |_ _   _| |_ ___ \n");
    printf("     | | | |\\/| | |     | |   | |______| |    / _ \\ \\ /\\ / / |    / _` | | | |/ _ \\ '__|______| || '_ \\/ __| __| | __| | | | __/ _ \\\n");
    printf("     | | | |  | | \\__/\\_| |_  | |      | |___| (_) \\ V  V /| |___| (_| | |_| |  __/ |        _| || | | \\__ \\ |_| | |_| |_| | ||  __/\n");
    printf("     \\_/ \\_|  |_/\\____/\\___/  \\_/      \\_____/\\___/ \\_/\\_/ \\_____/\\__,_|\\__, |\\___/_|        \\___/_| |_|___/\\__|_|\\__|\\__,_|\\__\\___|\n");
    printf("                                                                         __/ |                                                      \n");
    printf("                                                                        |___/                                                       \n");

    printf("\n");
    kinit();         // physical page allocator
    kvminit();       // create kernel page table
    kvminithart();   // turn on paging
    procinit();      // process table
    trapinit();      // trap vectors
    trapinithart();  // install kernel trap vector
    plicinit();      // set up interrupt controller
    plicinithart();  // ask PLIC for device interrupts
    binit();         // buffer cache
    iinit();         // inode table
    fileinit();      // file table
    virtio_disk_init(); // emulated hard disk
    userinit();      // first user process
    __sync_synchronize();
    started = 1;
  } else {
    while(started == 0)
      ;
    __sync_synchronize();
    printf("hart %d starting\n", cpuid());
    kvminithart();    // turn on paging
    trapinithart();   // install kernel trap vector
    plicinithart();   // ask PLIC for device interrupts
  }

  scheduler();        
}
