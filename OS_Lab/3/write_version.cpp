#include <bits/stdc++.h>

using namespace std;

int main()
{
	ofstream version_stream("/proc/version");
	if (version_stream << 'A' << endl)
		cout << "Success!" << endl;
	else
		cout << "Failure" << endl;
	version_stream.close();
}
