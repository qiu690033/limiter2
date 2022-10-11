#include <fstream>
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
using namespace std;

int x=24,y=31,z=28;
int cpu0[]={450000,500000,550000,600000,650000,700000,750000,800000,850000,900000,950000,1000000,1050000,1100000,1150000,1200000,1250000,1300000,1400000,1500000,1600000,1700000,1800000,1900000,2000000};
int cpu1[]={200000,300000,400000,500000,600000,700000,800000,900000,1000000,1100000,1200000,1300000,1400000,1500000,1600000,1700000,1800000,1900000,2000000,2050000,2100000,2150000,2200000,2250000,2300000,2350000,2400000,2450000,2550000,2650000,2750000,2850000};
int cpu2[]{500000,600000,700000,800000,900000,1000000,1100000,1200000,1300000,1400000,1500000,1600000,1700000,1800000,1900000,2000000,2050000,2100000,2150000,2200000,2250000,2300000,2350000,2400000,2450000,2550000,2650000,2750000,2850000};
long long power()
{
	
	long long curt,volt;
	ifstream current,voltage;
	current.open("/sys/class/power_supply/bms/current_now",ios::in);
	current >> curt;
	current.close();
	voltage.open("/sys/class/power_supply/bms/voltage_now",ios::in);
	voltage >> volt;
	voltage.close();
	return curt*volt/1000000000;
}
void freqwriter0(int n)
{
	chmod("/sys/devices/system/cpu/cpufreq/policy0/scaling_max_freq",S_IWRITE|S_IREAD);
	ofstream freqpoint0;
	freqpoint0.open("/sys/devices/system/cpu/cpufreq/policy0/scaling_max_freq", ios::out);
	freqpoint0 << cpu0[n];
	chmod("/sys/devices/system/cpu/cpufreq/policy0/scaling_max_freq",S_IREAD);
	freqpoint0.close();
}
void freqwriter1(int m)
{
	chmod("/sys/devices/system/cpu/cpufreq/policy4/scaling_max_freq",S_IWRITE|S_IREAD);
	ofstream freqpoint1;
	freqpoint1.open("/sys/devices/system/cpu/cpufreq/policy4/scaling_max_freq", ios::out);
	freqpoint1 << cpu1[m];
	chmod("/sys/devices/system/cpu/cpufreq/policy4/scaling_max_freq",S_IREAD);
	freqpoint1.close();
}
void freqwriter2(int d)
{
	chmod("/sys/devices/system/cpu/cpufreq/policy7/scaling_max_freq",S_IWRITE|S_IREAD);
	ofstream freqpoint2;
	freqpoint2.open("/sys/devices/system/cpu/cpufreq/policy7/scaling_max_freq", ios::out);
	freqpoint2 << cpu2[d];
	chmod("/sys/devices/system/cpu/cpufreq/policy7/scaling_max_freq",S_IREAD);
	freqpoint2.close();
}
long long usrpower()
{
    long long usr_power;
	ifstream target_power;
	target_power.open("/data/limit_power.conf");
	target_power >> usr_power;
	target_power.close();
	return usr_power;
}
int main()
{
	while (1<2)
	{
		{
			while(power()>usrpower())
			{
				   if (x>0&&y>0&&z>0)
				   {
				        x--;
				        y--;
				        z--;
				   }
				   freqwriter0(x);
				   freqwriter1(y);
				   freqwriter2(z);
				   usleep(500000);
				}
			}
			while(power()<usrpower())
			{
				   if(x<24)
				   {
    					x++;
						freqwriter0(x);
				   }
				   if(y<31)
				   {
				    	y++;
			    		freqwriter1(y);
				   }
			       if(z<28)
			       {
		    			z++;
				    	freqwriter2(z);
		    	   }
				    usleep(100000);
			    }
	}
	return 0;
}