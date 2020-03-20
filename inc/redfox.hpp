// General
#include <X11/Xlib.h>
#include <iostream>
#include <stdexcept>
#include <vector>

// Wifi
#include <ifaddrs.h>
#include <netinet/in.h>
#include <arpa/inet.h>

class Redfox
{
	int screen;
	std::vector<std::string> path_list = {
		"/sys/class/power_supply/BAT0/",
		"/sys/class/power_supply/BAT1/",
		"/sys/class/power_supply/BAT2/",
		"/sys/class/power_supply/BAT3/"};

	std::vector<std::string> full_list = {
		"energy_full", "charge_full", "current_full"};
	std::vector<std::string> now_list = {"energy_now", "charge_now",
						   "current_now"};

	std::string battery_path;

	ifaddrs *if_addr = nullptr;
	ifaddrs *ifa = nullptr;
	in_addr *tmp_ptr = nullptr;

	bool check_dir(const std::string dir) const;
	bool collect_info(std::string &path) const;

      public:
	Display *dpy;
	Window root;
	std::string output;

	Redfox()
	{
		if (!(dpy = XOpenDisplay(nullptr))) {
			std::cerr << "Could not open Display." << std::endl;
			throw std::invalid_argument("Could not open Display.");
		}
		screen = DefaultScreen(dpy);
		root = RootWindow(dpy, screen);
		collect_info(battery_path);
	}

  bool date(std::string &date) const;
	bool wifi(std::string &ip);
	bool battery(std::string &state, double &load) const;
	bool load_cpu_mem(double &cpu, long &mem) const;
	bool volume(long &vol) const;
};
