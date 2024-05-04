# SPDX-License-Identifier: BSD-3-Clause

import dbus

# get the system bus.
system_bus = dbus.SystemBus()

# use "get_object" on the "org.freedesktop.UPower" connection
# to obtain a handle to the "/org/freedesktop/UPower/devices/DisplayDevice" object.
proxy = system_bus.get_object("org.freedesktop.UPower", "/org/freedesktop/UPower/devices/DisplayDevice")

# call the "Get" method on the interface "org.freedesktop.DBus.Properties"
# and the arguments "org.freedesktop.UPower.Device" and "Percentage".
level = proxy.Get("org.freedesktop.UPower.Device", "Percentage", dbus_interface="org.freedesktop.DBus.Properties")

print(level)
