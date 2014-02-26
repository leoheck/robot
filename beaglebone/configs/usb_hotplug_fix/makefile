

src = usb_hotplug_fix

all:
	gcc -o $(src) $(src).c

clean:
	rm -rf $(src)

install:
	sed -i 's/exit 0//g' /etc/rc.local
	echo -e "\n/bin/$(src)" >> /etc/rc.local
	echo "exit 0" >> /etc/rc.local
