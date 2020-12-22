# AVR Programming - Timer Interrupts

**Overview**:
- Device : ATMega8
- Compare Match Interrupt A & B
- Using Timer 1
- CPU Clock : 5 MHz
- Simulate with Proteus / simulavr

**Simulating using `simulavr`**
1. Run `make` to get the list of available signals that you want to trace for the device. This will produce a file called `tracinglist.txt` and `signal-to-trace.txt`
    
        $ make get-tracing-list
    
2. Edit the `signal-to-trace.txt` file generated, then copy and paste some signals that you want to trace from the `tracinglist.txt` file.

3. Run make again to simulate, after around 4 seconds, force the simulation to stop by pressing Ctrl+C, since the microcontrollers run in infinite loops. This process may require longer time if you trace a lot of signals!
    
        $ make get-signal

4. After that, you can view the `.vcd` file using some tools like `gtkwave`
    
        $ gtkwave signal-to-trace.vcd
