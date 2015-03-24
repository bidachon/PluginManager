#include <pluginmanager.h>
#include <iostream>

int main(int argc,char **argv)
{
	plugin::PluginManager pm;
	if (argc != 2)
	{
		std::cerr << "Invalid number param:" << argc << std::endl;
		return 1;
	}
	pm.load(argv[1]);
	std::cerr << pm.errorMessage().toStdString()<< std::endl;
	
}