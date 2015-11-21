#include <sqlite3.h>

int main()
{
	Database db("tutorial.db");
	if (!db.Connected())
	{
		printf("Database not connected - exiting\n");
		exit(-1);
	}
}
