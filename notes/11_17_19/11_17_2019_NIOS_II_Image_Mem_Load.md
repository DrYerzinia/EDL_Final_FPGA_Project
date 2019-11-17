# (11/17/2019) Testing PIO Camera to NIOS II

I injected a counter signal into the data stream in the last byte.  A sample is shown below.  It seems we are unable to keep up with the
camera as the counter is going up by ~16 each time.  [0x00, 0x10, 0x23 0x3E, 0x51, 0x68]

53A500 252D10 262B23 27283E 2A2B51 292F68 353A84 515594 3333A8 758DC3 D3F5DA D1F6ED 6BAC04 6EAE1B 89C832 73BD40 262D4C 26295F 233072 242B89
2B2DA0 3033AF 3036C2 5256D5 2E35E8 565AFC D0F210 D4F627 95CD3A 4F7051 99CE64 70BE7F 2A2E90 252EA3 282FB6 282DCA 2A2CE1 2936F4 393904 3A481B
323626 4D5239 C2E048 D5F558 D4F568 95C87C 4C6F8C 88CA9C 8CCBB0 71BFC0 212DCD 2330DD 242EF1 262F01 292D11 2C2E25 303638 373D47 4D4F5B 34386A
678481 CFF491 D8F5A1 ADD6B5 4884C5 4B75D5 97CEE5 81C5F9 272B12 233025 282935 2A2B45 2C2D55 283269 2D3575 45478E 2D2DA5 545ABC D3F5CF 95C7FB

Changing tactics using University Program video core IP.  Trying Video DMA Controller.  First pass feeding with Test Generator.

To get BSP to build had to comment out line 87 of altera_up_avalon_video_dma_controller.tcl as it referenced a *_rgb.h which does not exist.

