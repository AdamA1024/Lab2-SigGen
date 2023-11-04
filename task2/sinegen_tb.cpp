#include "Vsinegen.h"
#include "verilated.h"
#include "verilated_vcd_c.h"
#include "vbuddy.cpp"
int main(int argc, char **argv, char **env)
{
    int i;
    int clk;

    Verilated::commandArgs(argc, argv);
    Vsinegen *top = new Vsinegen;

    Verilated::traceEverOn(true);
    VerilatedVcdC *tfp = new VerilatedVcdC;
    top->trace(tfp, 99);
    tfp->open("sinegen.vcd");

    // init Vbuddy
    if (vbdOpen() != 1)
    {
        return (-1);
    }
    vbdHeader("Lab2T2: SigGen");
    top->clk = 1;
    top->rst = 0;
    top->en = 1;
    top->incr = 5;
    top->offset = 64;

    for (i = 0; i < 1000000; i++)
    {
        for (clk = 0; clk < 2; clk++)
        {
            tfp->dump(2 * i + clk);
            top->clk = !top->clk;
            top->eval();
        }
        top->offset = vbdValue();
        vbdPlot(int(top->data1), 0, 255);
        vbdPlot(int(top->data2), 0, 255);
        vbdCycle(i);
        // either simulation finished, or 'q' is pressed
        if ((Verilated::gotFinish()) || (vbdGetkey() == 'q'))
        {
            exit(0);
        }
        // ... exit if finish OR 'q' pressed
    }
}