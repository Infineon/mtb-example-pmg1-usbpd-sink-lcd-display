# EZ-PD&trade; PMG1 MCU: USB PD sink with 16x2 LCD

This code example demonstrates USB Power Delivery (PD) sink functionality and displays the PD contract information such as the type of PD source connected, negotiated voltage and current on LCD, and PWM to control the brightness of the LCD using EZ-PD&trade; PMG1 MCU devices.


[View this README on GitHub.](https://github.com/Infineon/mtb-example-pmg1-usbpd-sink-lcd-display)

[Provide feedback on this code example.](https://cypress.co1.qualtrics.com/jfe/form/SV_1NTns53sK2yiljn?Q_EED=eyJVbmlxdWUgRG9jIElkIjoiQ0UyMzY4MjIiLCJTcGVjIE51bWJlciI6IjAwMi0zNjgyMiIsIkRvYyBUaXRsZSI6IkVaLVBEJnRyYWRlOyBQTUcxIE1DVTogVVNCIFBEIHNpbmsgd2l0aCAxNngyIExDRCIsInJpZCI6Im5zaCIsIkRvYyB2ZXJzaW9uIjoiMS4wLjAiLCJEb2MgTGFuZ3VhZ2UiOiJFbmdsaXNoIiwiRG9jIERpdmlzaW9uIjoiTUNEIiwiRG9jIEJVIjoiV0lSRUQiLCJEb2MgRmFtaWx5IjoiVFlQRS1DIn0=)

## Requirements

- [ModusToolbox&trade; software](https://www.infineon.com/modustoolbox) v3.0 or later (tested with v3.0)
- Board support package (BSP) minimum required version: 3.0.0
- Programming language: C
- Associated parts: All [EZ-PD&trade; PMG1 MCU](https://www.infineon.com/PMG1) parts
- 16x2 LCD Module

## Supported toolchains (make variable 'TOOLCHAIN')

- GNU Arm&reg; Embedded Compiler v10.3.1 (`GCC_ARM`) - Default value of `TOOLCHAIN`
- Arm&reg; Compiler v6.13 (`ARM`)
- IAR C/C++ Compiler v8.42.2 (`IAR`)


## Supported kits (make variable 'TARGET')

- [EZ-PD&trade; PMG1-S0 prototyping kit](https://www.infineon.com/CY7110) (`PMG1-CY7110`) - Default value of `TARGET`
- [EZ-PD&trade; PMG1-S1 prototyping kit](https://www.infineon.com/CY7111) (`PMG1-CY7111`)
- [EZ-PD&trade; PMG1-S2 prototyping kit](https://www.infineon.com/CY7112) (`PMG1-CY7112`)
- [EZ-PD&trade; PMG1-S3 prototyping kit](https://www.infineon.com/CY7113) (`PMG1-CY7113`)

## Hardware setup

1. Connect the board to your PC using the USB cable through the KitProg3 USB Type-C port (J1). This cable is used for programming the PMG1 device. It is also used during debugging.

2. Connect a USB PD source to the PMG1 USB PD port (J10) through a USB Type-C cable. This cable is used for powering the device

3. Connect the 16x2 LCD pins to the PMG1 kits per Table 1:

**Table 1. 16x2 LCD pin connection for PMG1 kits**

 | LCD 16x2 pins  | PMG1-S0 | PMG1-S1 | PMG1-S2 | PMG1-S3
 | :-------       | :------------ | :----------     | :---------- |  :---------- |
 | VSS | GND   | GND   | GND   | GND
 | VDD | 3V3   | 3V3   | 3V3   | 3V3
 | RS  | J7.12 | J7.16 | J7.14 | J7.9
 | RW  | J7.11 | J7.15 | J7.13 | J7.8
 | E   | J7.8  | J7.13 | J7.12 | J7.7
 | D4  | J7.6  | J7.12 | J7.11 | J7.6
 | D5  | J7.9  | J7.11 | J7.8  | J7.5
 | D6  | J6.9  | J7.8  | J7.5  | J7.4
 | D7  | J6.10 | J6.15 | J7.4  | J6.19
 | A   | J7.7  | J6.16 | J6.11 | J7.11
 | K   | GND   | GND   | GND   | GND

**Figure 1. Interface block diagram**

<img src = "images/block_diagram.png" width = "600"/>

See the kit user guide for more details on configuring the board.

## Software setup

This example requires no additional software or tools.


## Using the code example

Create the project and open it using one of the following:

<details><summary><b>In Eclipse IDE for ModusToolbox&trade; software</b></summary>

1. Click the **New Application** link in the **Quick Panel** (or, use **File** > **New** > **ModusToolbox&trade; Application**). This launches the [Project Creator](https://www.infineon.com/ModusToolboxProjectCreator) tool.

2. Pick a kit supported by the code example from the list shown in the **Project Creator - Choose Board Support Package (BSP)** dialog.

   When you select a supported kit, the example is reconfigured automatically to work with the kit. To work with a different supported kit later, use the [Library Manager](https://www.infineon.com/ModusToolboxLibraryManager) to choose the BSP for the supported kit. You can use the Library Manager to select or update the BSP and firmware libraries used in this application. To access the Library Manager, click the link from the **Quick Panel**.

   You can also just start the application creation process again and select a different kit.

   If you want to use the application for a kit not listed here, you may need to update the source files. If the kit does not have the required resources, the application may not work.

3. In the **Project Creator - Select Application** dialog, choose the example by enabling the checkbox.

4. (Optional) Change the suggested **New Application Name**.

5. The **Application(s) Root Path** defaults to the Eclipse workspace which is usually the desired location for the application. If you want to store the application in a different location, you can change the *Application(s) Root Path* value. Applications that share libraries should be in the same root path.

6. Click **Create** to complete the application creation process.

For more details, see the [Eclipse IDE for ModusToolbox&trade; software user guide](https://www.infineon.com/MTBEclipseIDEUserGuide) (locally available at *{ModusToolbox&trade; software install directory}/docs_{version}/mt_ide_user_guide.pdf*).

</details>

<details><summary><b>In command-line interface (CLI)</b></summary>

ModusToolbox&trade; software provides the Project Creator as both a GUI tool and the command line tool, "project-creator-cli". The CLI tool can be used to create applications from a CLI terminal or from within batch files or shell scripts. This tool is available in the *{ModusToolbox&trade; software install directory}/tools_{version}/project-creator/* directory.

Use a CLI terminal to invoke the "project-creator-cli" tool. On Windows, use the command line "modus-shell" program provided in the ModusToolbox&trade; software installation instead of a standard Windows command-line application. This shell provides access to all ModusToolbox&trade; software tools. You can access it by typing `modus-shell` in the search box in the Windows menu. In Linux and macOS, you can use any terminal application.

The "project-creator-cli" tool has the following arguments:

Argument | Description | Required/optional
---------|-------------|-----------
`--board-id` | Defined in the `<id>` field of the [BSP](https://github.com/Infineon?q=bsp-manifest&type=&language=&sort=) manifest | Required
`--app-id`   | Defined in the `<id>` field of the [CE](https://github.com/Infineon?q=ce-manifest&type=&language=&sort=) manifest | Required
`--target-dir`| Specify the directory in which the application is to be created if you prefer not to use the default current working directory | Optional
`--user-app-name`| Specify the name of the application if you prefer to have a name other than the example's default name | Optional

<br>

The following example clones the "[USB PD sink with 16x2 LCD](https://github.com/Infineon/mtb-example-pmg1-usbpd-sink-lcd-display)" application with the desired name "MyUsbPdSinkLcdDisplay" configured for the *PMG1-CY7110* BSP into the specified working directory, *C:/mtb_projects*:

   ```
   project-creator-cli --board-id PMG1-CY7110 --app-id mtb-example-pmg1-usbpd-sink-lcd-display --user-app-name MyUsbPdSinkLcdDisplay --target-dir "C:/mtb_projects"
   ```

**Note:** The project-creator-cli tool uses the `git clone` and `make getlibs` commands to fetch the repository and import the required libraries. For details, see the "Project creator tools" section of the [ModusToolbox&trade; software user guide](https://www.infineon.com/ModusToolboxUserGuide) (locally available at *{ModusToolbox&trade; software install directory}/docs_{version}/mtb_user_guide.pdf*).

To work with a different supported kit later, use the [Library Manager](https://www.infineon.com/ModusToolboxLibraryManager) to choose the BSP for the supported kit. You can invoke the Library Manager GUI tool from the terminal using `make library-manager` command or use the Library Manager CLI tool "library-manager-cli" to change the BSP.

The "library-manager-cli" tool has the following arguments:

Argument | Description | Required/optional
---------|-------------|-----------
`--add-bsp-name` | Name of the BSP that should be added to the application | Required
`--set-active-bsp` | Name of the BSP that should be as active BSP for the application | Required
`--add-bsp-version`| Specify the version of the BSP that should be added to the application if you do not wish to use the latest from manifest | Optional
`--add-bsp-location`| Specify the location of the BSP (local/shared) if you prefer to add the BSP in a shared path | Optional

<br>

The following example adds the PMG1-CY7110 BSP to the already created application and makes it the active BSP for the app:

   ```
   ~/ModusToolbox/tools_3.0/library-manager/library-manager-cli --project "C:/mtb_projects/MyUsbPdSinkLcdDisplay" --add-bsp-name PMG1-CY7110--add-bsp-version "latest-v3.X" --add-bsp-location "local"

   ~/ModusToolbox/tools_3.0/library-manager/library-manager-cli --project "C:/mtb_projects/MyUsbPdSinkLcdDisplay" --set-active-bsp APP_PMG1-CY7110

   ```

</details>

<details><summary><b>In third-party IDEs</b></summary>

Use one of the following options:

- **Use the standalone [Project Creator](https://www.infineon.com/ModusToolboxProjectCreator) tool:**

   1. Launch Project Creator from the Windows Start menu or from *{ModusToolbox&trade; software install directory}/tools_{version}/project-creator/project-creator.exe*.

   2. In the initial **Choose Board Support Package** screen, select the BSP, and click **Next**.

   3. In the **Select Application** screen, select the appropriate IDE from the **Target IDE** drop-down menu.

   4. Click **Create** and follow the instructions printed in the bottom pane to import or open the exported project in the respective IDE.

<br>

- **Use command-line interface (CLI):**

   1. Follow the instructions from the **In command-line interface (CLI)** section to create the application.

   2. Export the application to a supported IDE using the `make <ide>` command.

   3. Follow the instructions displayed in the terminal to create or import the application as an IDE project.

For a list of supported IDEs and more details, see the "Exporting to IDEs" section of the [ModusToolbox&trade; software user guide](https://www.infineon.com/ModusToolboxUserGuide) (locally available at *{ModusToolbox&trade; software install directory}/docs_{version}/mtb_user_guide.pdf*).

</details>

## Operation

1. Ensure that the steps listed in the [Hardware setup](#hardware-setup) section are completed.

2. Ensure that the jumper shunt on power selection jumper (J5) is placed at position 2-3 to enable programming mode.

3. Connect the board to your PC using the USB cable through the KitProg3 USB connector (J1). This cable is used for programming the PMG1 device.

4. Program the board using one of the following:

   <details><summary><b>Using Eclipse IDE for ModusToolbox&trade; software</b></summary>

      1. Select the application project in the Project Explorer.

      2. In the **Quick Panel**, scroll down, and click **\<Application Name> Program (KitProg3_MiniProg4)**.
   </details>

   <details><summary><b>Using CLI</b></summary>

     From the terminal, execute the `make program` command to build and program the application using the default toolchain to the default target. The default toolchain is specified in the application's Makefile but you can override this value manually:
      ```
      make program TOOLCHAIN=<toolchain>
      ```

      Example:
      ```
      make program TOOLCHAIN=GCC_ARM
      ```
   </details>

5. After programming the kit, change the position on power selection jumper (J5) to 1-2 to power the kit through the USB PD port (J10). Do not change the jumper (J5) position while the cables are connected to power source.

6. Observe that the user LED (LED3) on the board blinks at different rates depending on the type of power adapter connected:

   - If a power adapter supporting USB Power Delivery is connected, the LED blinks at approximately 5 Hz (toggles every 100 ms); the LCD displays **PD Power Source** in the first row and PDO details (voltage and current) in the second row.

   - If a USB Type-C power adapter or a standard downstream port (SDP) is connected, the LED blinks at approximately 1 Hz (toggles every 500 ms); the LCD displays **SDP source** in the first row.

   - If a dedicated charging port (DCP) is connected, the LED blinks at approximately 0.17 Hz (toggles every 3 seconds); the LCD displays **DCP source** in the first row.

   - If a charging downstream port (CDP) is connected, the LED blinks at approximately 0.05 Hz (toggles every 10 seconds); the LCD displays **CDP source** in the first row.

7. Control the brightness of the LCD via the `PWM_DUTY_CYCLE` macro defined in the *src/lcd/lcd.h* header file.
	- `PWM_DUTY_CYCLE` set to 0U: Brightness of the LCD module is 0%
	- `PWM_DUTY_CYCLE` set to 100U: Brightness of the LCD module is 100%

8. Observe that every 3 seconds, the LCD is updated with the connected PD source and contract data.

9. Measure the negotiated VBUS voltage using a multimeter across the DC_OUT terminal block (J9).

**Figure 2. LCD output for PD power source**

<img src = "images/lcd_output_pd_power_source.jpg" width = "300"/>

## Debugging

You can debug the example to step through the code. In the IDE, use the **\<Application name> Debug (KitProg3_MiniProg4)** configuration in the **Quick Panel**.

Ensure that the board is connected to your PC using the USB cables through both the KitProg3 USB connector as well as the USB PD port, with the jumper shunt on power selection jumper (J5) placed at position 1-2.

See the "Debug mode" section in the kit user guide for debugging the application on the CY7110 prototyping kit. For more details, see the "Program and debug" section in the [Eclipse IDE for ModusToolbox&trade; software user guide](https://www.infineon.com/MTBEclipseIDEUserGuide).

## Design and implementation

### Interfacing the LCD

This code example uses a SDCB1602-01 16x2 LCD module, which has 16 columns and 2 rows to display data, and uses a parallel interface to communicate with the MCU. The LCD has 8-bit and 4-bit interface modes. This code example uses the 4-bit interface mode.

The LCD has two registers (command and data registers); the command register stores various commands given to the display. The data register stores data to be displayed.


**Figure 3. LCD 16x2 pinout**

<img src = "images/16x2_lcd_module_pinout.png" width = "300"/>

**Table 2. LCD pinout**

| Pin number | Pin name | Function description |
| :-------  | :------------ | :----------------|
| 1 | VSS | Ground (GND)|
| 2 | VCC | 3.3 V |
| 3 | VO  | Adjust the contrast of the LCD |
| 4 | RS (Register Select) | Toggle between command and data register. For command, RS = 0; for data, RS = 1 |
| 5 | RW (Read Write) | Used for read/write operation. For write, RW = 0; for read, RW = 1 |
| 6 | EN (Enable) | Toggled for read/write operations |
| 7 - 14 | D0–D7 (Data pins) | Used to send data/command |
| 15 | A (Anode) | Used for backlight (positive terminal) |
| 16 | K (Cathode) | Used for backlight (negative terminal) |

### LCD modes

 - 4-bit mode: Sends the data nibble by nibble, first the upper nibble and then the lower nibble, and uses data pins D4–D7
 - 8-bit mode: Sends the data directly and uses data pins D0–D7

**Table 3. 16x2 LCD general commands**

 | Hex codes | Command to LCD display |
 | :-------  | :------------ |
 | 0x01 | Clear display   |
 | 0x02 | Return home     |
 | 0x04 | Decrement cursor (shift cursor left) |
 | 0x06 | Increment cursor (shift cursor right) |
 | 0x05 | Shift display right  |
 | 0x07 | Shift display left  |
 | 0x0A | Cursor ON, display OFF  |
 | 0x0C | Cursor OFF, display ON  |
 | 0x0F | Display ON, blinks the cursor |
 | 0x10 | Shift cursor position left |
 | 0x14 | Shift cursor position right |
 | 0x18 | Shift the entire display left |
 | 0x1C | Shift the entire display right |
 | 0x80 | Move cursor to the beginning of the first line |
 | 0xC0 | Move cursor to the beginning of the second line |
 | 0x38 | 2 lines and 5x7 matrix |

**Note:** See the datasheet of [SDCB1602-01 16x2 LCD module](https://5.imimg.com/data5/HR/NS/JC/SELLER-3287828/16xx01-cob-lcd-display.pdf) for more details.

### USB PD sink

See [EZ-PD™ PMG1 MCU: USBPD sink](https://github.com/Infineon/mtb-example-pmg1-usbpd-sink) to learn about the PD sink functionality.

**Figure 4. Firmware flowchart**

<img src = "images/firmwareflowchart.png" width = "500"/>`

### Resources and settings

**Table 4. Application resources**

| Resource  | Alias/object   | Purpose                               |
| :-------  | :------------  | :------------------------------------ |
| USBPD     | PD_PORT0       | USBPD block used for PD communication |
| LED (BSP) | CYBSP_USER_LED | User LED to indicate PD connection state |
| TCPWM (PWM) | CYBSP_PWM | To control the backlighting brightness of the LCD |

<br>

## Related resources

Resources | Links
-----------|------------------
Application notes |[AN232553](https://www.infineon.com/AN232553) – Getting started with EZ-PD&trade; PMG1 MCU on ModusToolbox&trade; software <br> [AN232565](https://www.infineon.com/an232565) – EZ-PD&trade; PMG1 hardware design guidelines and checklist
Code examples  | [Using ModusToolbox&trade; software](https://github.com/Infineon/Code-Examples-for-ModusToolbox-Software) on GitHub
Device documentation | [EZ-PD&trade; PMG1 MCU datasheets](https://www.infineon.com/PMG1DS)
Development kits | Select your kits from the [Evaluation Board Finder](https://www.infineon.com/cms/en/design-support/finder-selection-tools/product-finder/evaluation-board) page.
Libraries on GitHub | [mtb-pdl-cat2](https://github.com/Infineon/mtb-pdl-cat2) – Peripheral driver library (PDL) and docs
Tools | [Eclipse IDE for ModusToolbox&trade; software](https://www.infineon.com/modustoolbox) <br> ModusToolbox&trade; software is a collection of easy-to-use software and tools enabling rapid development with Infineon MCUs, covering applications from embedded sense and control to wireless and cloud-connected systems using AIROC™ Wi-Fi & Bluetooth® combo devices.


## Other resources

Infineon provides a wealth of data at www.infineon.com to help you select the right device, and quickly and effectively integrate it into your design.


## Document history

Document title: *CE236822* – *EZ-PD&trade; PMG1 MCU: USB PD sink with 16x2 LCD*

| Version | Description of change |
| ------- | --------------------- |
| 1.0.0   | New code example      |

<br>

---------------------------------------------------------

© Cypress Semiconductor Corporation, 2022-2023. This document is the property of Cypress Semiconductor Corporation, an Infineon Technologies company, and its affiliates (“Cypress”). This document, including any software or firmware included or referenced in this document (“Software”), is owned by Cypress under the intellectual property laws and treaties of the United States and other countries worldwide. Cypress reserves all rights under such laws and treaties and does not, except as specifically stated in this paragraph, grant any license under its patents, copyrights, trademarks, or other intellectual property rights. If the Software is not accompanied by a license agreement and you do not otherwise have a written agreement with Cypress governing the use of the Software, then Cypress hereby grants you a personal, non-exclusive, nontransferable license (without the right to sublicense) (1) under its copyright rights in the Software (a) for Software provided in source code form, to modify and reproduce the Software solely for use with Cypress hardware products, only internally within your organization, and (b) to distribute the Software in binary code form externally to end users (either directly or indirectly through resellers and distributors), solely for use on Cypress hardware product units, and (2) under those claims of Cypress’s patents that are infringed by the Software (as provided by Cypress, unmodified) to make, use, distribute, and import the Software solely for use with Cypress hardware products. Any other use, reproduction, modification, translation, or compilation of the Software is prohibited.
<br>
TO THE EXTENT PERMITTED BY APPLICABLE LAW, CYPRESS MAKES NO WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, WITH REGARD TO THIS DOCUMENT OR ANY SOFTWARE OR ACCOMPANYING HARDWARE, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. No computing device can be absolutely secure. Therefore, despite security measures implemented in Cypress hardware or software products, Cypress shall have no liability arising out of any security breach, such as unauthorized access to or use of a Cypress product. CYPRESS DOES NOT REPRESENT, WARRANT, OR GUARANTEE THAT CYPRESS PRODUCTS, OR SYSTEMS CREATED USING CYPRESS PRODUCTS, WILL BE FREE FROM CORRUPTION, ATTACK, VIRUSES, INTERFERENCE, HACKING, DATA LOSS OR THEFT, OR OTHER SECURITY INTRUSION (collectively, “Security Breach”). Cypress disclaims any liability relating to any Security Breach, and you shall and hereby do release Cypress from any claim, damage, or other liability arising from any Security Breach. In addition, the products described in these materials may contain design defects or errors known as errata which may cause the product to deviate from published specifications. To the extent permitted by applicable law, Cypress reserves the right to make changes to this document without further notice. Cypress does not assume any liability arising out of the application or use of any product or circuit described in this document. Any information provided in this document, including any sample design information or programming code, is provided only for reference purposes. It is the responsibility of the user of this document to properly design, program, and test the functionality and safety of any application made of this information and any resulting product. “High-Risk Device” means any device or system whose failure could cause personal injury, death, or property damage.  Examples of High-Risk Devices are weapons, nuclear installations, surgical implants, and other medical devices. “Critical Component” means any component of a High-Risk Device whose failure to perform can be reasonably expected to cause, directly or indirectly, the failure of the High-Risk Device, or to affect its safety or effectiveness. Cypress is not liable, in whole or in part, and you shall and hereby do release Cypress from any claim, damage, or other liability arising from any use of a Cypress product as a Critical Component in a High-Risk Device. You shall indemnify and hold Cypress, including its affiliates, and its directors, officers, employees, agents, distributors, and assigns harmless from and against all claims, costs, damages, and expenses, arising out of any claim, including claims for product liability, personal injury or death, or property damage arising from any use of a Cypress product as a Critical Component in a High-Risk Device. Cypress products are not intended or authorized for use as a Critical Component in any High-Risk Device except to the limited extent that (i) Cypress’s published data sheet for the product explicitly states Cypress has qualified the product for use in a specific High-Risk Device, or (ii) Cypress has given you advance written authorization to use the product as a Critical Component in the specific High-Risk Device and you have signed a separate indemnification agreement.
<br>
Cypress, the Cypress logo, and combinations thereof, WICED, ModusToolbox, PSoC, CapSense, EZ-USB, F-RAM, and Traveo are trademarks or registered trademarks of Cypress or a subsidiary of Cypress in the United States or in other countries. For a more complete list of Cypress trademarks, visit cypress.com. Other names and brands may be claimed as property of their respective owners.
