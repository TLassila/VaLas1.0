# VaLas1.0
Manual 722.6 controller, with support for 0,91" oled display which is easily placed on w124 gauge cluster for mimicking oem appearance.

Goal for this project was to create very simple and cheap controller, which is also user friendly to adjust and drive daily.
This contoller is now being used on 4 different vehicles with varying power output from estimated 250-500whp & +700nm of torque. My personal vehicle has been driven past +10 000km/10 months period, basically trouble free and daily driving with same code. 
My vehicle specs: om606+8mm pump, he531 turbocharger, 722.6 from 270 cdi(+500k odo).

Controller has gears 1-5+. Gears 1-5 are normal gears, and 5+ is overdrive gear which will lock turbine and reduce line pressure in transmission for reduced consumption when coasting +80km/h. Oled display helps knowing which gear you are, since this controller has no means to know it by its own.

How to use:
When vehicle is started, use relay to turn controller on with gearbox in P.
Controller should now start, displaying GEAR 2 which means controller is in gear 2.
Now you can use shifter freely between P-R-N-D, MAKE SURE YOU ALWAYS SHIFT P-R-N-D WITH CONTROLLER IN GEAR 2 except when turning vehicle+contorller off, which can be done in any gear.

When in position D, you can use 2 electric switches for contolling gears 1-5+, shifts are completed as whole, and cannot be overlapped even if switch is stuck at either +/- position.

Code and adjustments are from my vehicle, and should work smoothly even in paved surfaces. Shifting from 3-4 is meant for undrilled gearbox valve plate. After drilling valve plate, you can use base adjustments of 3-4 shift and tune from that.

Transmission has 6 solenoids controlled by arduino:

Shift pc     : pressure apllied during shifts :adjustment range 0-255 0=low pressure, pwm
Mod pc       : pressure apllied when in gear  :adjustment range 0-255 0=low pressure, pwm
Tcc          : engages turbine lock           :adjustment range 0-255 0=low pressure, pwm
Shift 1-2,4-5: applied during shifts          :adjustment range LOW-HIGH
Shift 2-3    : applied during shifts          :adjustment range LOW-HIGH
Shift 3-4    : applied during shifts          :adjustment range LOW-HIGH

Made by Toni Lassila
Coding and pcb made with Teemu Vahtola

If you are looking for more advanced controller with automatic shifts, speedo and many more features, please take a look https://github.com/mkovero/7226ctrl by Markus Kovero.

04/2018 First tests and drives in completed in 04/2018.
06/2018 0,91" Oled added.
6/2018 Latest adjustments to controller code.
