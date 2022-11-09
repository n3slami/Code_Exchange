#include <bits/stdc++.h>

using namespace std;

int main()
{
	ifstream version_stream("/proc/version");
	stringstream buffer;
	buffer << version_stream.rdbuf();

	ofstream output("./Linux Version.txt");
	output << buffer.str();
	output.close();
	version_stream.close();
}
