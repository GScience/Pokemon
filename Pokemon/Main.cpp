
#include "Application.h"

void onKey(int key, keyAction action)
{
	
}
int main(int argc, char* args[])
{
	Application app("123");
	app.keyEvent += onKey;

	app.run();

	return 0;
}