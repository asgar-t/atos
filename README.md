# atOS Project 🚀

## Motivation
I built this project because I wanted to get hands-on experience with **embedded systems** and to understand how **operating systems really work under the hood**. Instead of just reading about kernels, paging, and drivers, I wanted to actually *write the code* that makes it all happen — from the ground up.

## Features ✨
- **Keyboard driver**: Low-level keyboard input handling using scan codes.  
- **Graphics driver**: Basic VGA graphics output to render text and pixels.  
- **Bootloader + Kernel**: Custom bootstrapping with paging enabled and higher-half kernel support.  
- **Memory management**: Page directory setup, physical vs. virtual memory mapping.  
- **Multiboot compliant**: Boots cleanly via GRUB into protected mode.  

## Things I Learned 📚
This project was a deep dive into the "bare metal" side of computing:
- **Low-level assembly and C**: Writing startup code, managing registers, and linking everything together.  
- **Operating systems internals**: Bootloading, memory management, and basic kernel design.  
- **Memory architecture**: Paging, physical/virtual addressing, and higher-half kernels.  
- **Driver development**: Building graphics and keyboard drivers from scratch.  
- **Embedded systems mindset**: Thinking about constraints, direct hardware access, and debugging at the lowest level.  

## Next Steps 🔮
- Add more device drivers (mouse, disk).  
- Implement a basic scheduler and multitasking.  
- Explore file systems integration.  
