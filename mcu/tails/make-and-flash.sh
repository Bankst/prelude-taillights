make -C build -j
openocd -f interface/cmsis-dap.cfg -f target/rp2040.cfg -c "adapter speed 10000" -c "program build/picow-ludeled.elf verify reset exit"