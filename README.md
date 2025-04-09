# sc4-humane-society-ordinance

A DLL Plugin for SimCity 4 that adds a Humane Society ordinance to the game.   
This ordinance is based on the Humane Society ordinance suggestion in [this](https://community.simtropolis.com/forums/topic/26215-ordinances-complete-list/?do=findComment&comment=703433) post, and has the following properties:

**Availability Requirements:** At least 1 hospital or clinic. The original suggestion did not include this, but I think it makes sense given the per hospital/clinic cost.      
**Expense:** `Base cost of $-50/month plus $-5 per hospital/clinic`.    
**Effects:**
* Increases mayor rating by 5 points.
* Reduces crime by 5%.

The plugin can be downloaded from the Releases tab: https://github.com/0xC0000054/sc4-humane-society-ordinance/releases

This plugin also serves as a demonstration of how to create a custom ordinance DLL with availability requirements and a custom monthly cost calculation.

## System Requirements

* Windows 10 or later

The plugin may work on Windows 7 or later with the [Microsoft Visual C++ 2022 x86 Redistribute](https://aka.ms/vs/17/release/vc_redist.x86.exe) installed, but I do not have to ability to test that.

## Installation

1. Close SimCity 4.
2. Copy `SC4HumaneSocietyOrdinance.dll` and `HumaneSocietyOrdinanceText_English.dat` into the Plugins folder in the SimCity 4 installation directory.
3. Start SimCity 4.

## Troubleshooting

The plugin should write a `SC4HumaneSocietyOrdinance.log` file in the same folder as the plugin.    
The log contains status information for the most recent run of the plugin.

# License

This project is licensed under the terms of the MIT License.    
See [LICENSE.txt](LICENSE.txt) for more information.

## 3rd party code

[gzcom-dll](https://github.com/nsgomez/gzcom-dll/tree/master) Located in the vendor folder, MIT License.    
[Windows Implementation Library](https://github.com/microsoft/wil) MIT License    

# Source Code

## Prerequisites

* Visual Studio 2022

## Building the plugin

* Open the solution in the `src` folder
* Update the post build events to copy the build output to you SimCity 4 application plugins folder.
* Build the solution

## Debugging the plugin

Visual Studio can be configured to launch SimCity 4 on the Debugging page of the project properties.
I configured the debugger to launch the game in a window with the following command line:    
`-intro:off -CPUcount:1 -w -CustomResolution:enabled -r1920x1080x32`

You may need to adjust the resolution for your screen.

## Source Code Layout

[HumaneSocietyOrdinanceDllDirector.cpp](src/HumaneSocietyOrdinanceDllDirector.cpp) is the main plugin file. It handles the setup that SC4 requires to load a DLL, and adding the ordinance into the game.

[HumaneSocietyOrdinance.h](src/HumaneSocietyOrdinance.h) defines the methods that the ordinance overrides for its custom behavior.    
[HumaneSocietyOrdinance.cpp](src/HumaneSocietyOrdinance.cpp) provides the implementation for the methods that the ordinance overrides.

[OrdinanceBase.cpp](src/OrdinanceBase.cpp) is the base class for `HumaneSocietyOrdinance`. It handles the common logic for a custom ordinance.
[OrdinancePropertyHolder.cpp](src/OrdinancePropertyHolder.cpp) provides the game with a list of effects that should be applied when the ordinance is enabled.
The effects can include Mayor Rating boosts, Demand boosts, etc.
