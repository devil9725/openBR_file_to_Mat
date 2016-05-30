
#include <QtCore/QCoreApplication>
#include "Windows.h"
#include <stdio.h>
#include <string>
#include <comdef.h>
#include <QtCore/QCoreApplication>
#include <openbr/openbr_plugin.h>
#include <QFile>
#include <stdio.h>
#include <QDataStream>
#include <QSharedPointer>
#pragma comment (lib, "opencv_core2411.lib")



wchar_t *convertCharArrayToLPCWSTR(const char* charArray)
{
	wchar_t* wString = new wchar_t[MAX_PATH];
	MultiByteToWideChar(CP_ACP, 0, charArray, -1, wString, MAX_PATH);
	return wString;
}

void putArrayToFile(char * from_file, char* to_file, QSharedPointer<br::Transform> transform)
{
	br::Template queryA(from_file);

	queryA >> *transform;

		
	QString filename = to_file;
	QFile file(filename);

	if (file.open(QIODevice::ReadWrite))
	{
		QDataStream stream(&file);
		stream << queryA;
	}

	file.close();
}

bool getPhotoFiles(char * from_dir, char * to_dir){
	QSharedPointer<br::Transform> transform = br::Transform::fromAlgorithm("FaceRecognition");
	WIN32_FIND_DATA fd;
	HANDLE hFind;
	char * f_dir = new char[MAX_PATH];
	strcpy(f_dir, from_dir);
	strcat(f_dir, "*.jpg");
	wchar_t *fPath;
	fPath = convertCharArrayToLPCWSTR(f_dir);
	hFind = FindFirstFile(convertCharArrayToLPCWSTR(f_dir), &fd);
	if (!hFind) return false;
	if ((wcscmp(fd.cFileName, L".") != 0) && (wcscmp(fd.cFileName, L"..") != 0)){

		char * full_file_name = new char[MAX_PATH];
		char * full_outfile_name = new char[MAX_PATH];
		_bstr_t b(fd.cFileName);
		const char* c = b;
		strcpy(full_file_name, from_dir);
		strcpy(full_outfile_name, to_dir);
		strcat(full_file_name, c);
		strcat(full_outfile_name, c);
		strcat(full_outfile_name, ".f");
		printf("%s\n", full_outfile_name);
		putArrayToFile(full_file_name, full_outfile_name, transform);

	}
	while (FindNextFile(hFind, &fd)){
		if ((wcscmp(fd.cFileName, L".") != 0) && (wcscmp(fd.cFileName, L"..") != 0)){

			char * full_file_name = new char[MAX_PATH];
			char * full_outfile_name = new char[MAX_PATH];
			_bstr_t b(fd.cFileName);
			const char* c = b;
			strcpy(full_file_name, from_dir);
			strcpy(full_outfile_name, to_dir);
			strcat(full_file_name, c);
			strcat(full_outfile_name, c);
			strcat(full_outfile_name, ".f");
			printf("%s\n", full_outfile_name);
			putArrayToFile(full_file_name, full_outfile_name, transform);

		}
	}
	return true;
}


int main(int argc, char *argv[])
{

	if (argc != 3) return 1;
	
	br::Context::initialize(argc, argv);
		
	getPhotoFiles(argv[1], argv[2]);
		
	br::Context::finalize();
	
	return 0;
}
