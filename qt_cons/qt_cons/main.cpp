
#include <QtCore/QCoreApplication>





#include <stdio.h>

//#include <curl/types.h>
//#include <curl/easy.h>
#include <string>




#include <QtCore/QCoreApplication>
#include <openbr/openbr_plugin.h>
#include <QFile>
#include <stdio.h>
#include <QDataStream>
#include <QSharedPointer>
#pragma comment (lib, "opencv_core2411.lib")




size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) {
	size_t written;
	written = fwrite(ptr, size, nmemb, stream);
	return written;
}
//using namespace cv;
int main(int argc, char *argv[])
{
	



	//QCoreApplication a(argc, argv);
	
	br::Context::initialize(argc, argv);

	// Retrieve classes for enrolling and comparing templates using the FaceRecognition algorithm
	QSharedPointer<br::Transform> transform = br::Transform::fromAlgorithm("FaceRecognition");
	//QSharedPointer<br::Distance> distance = br::Distance::fromAlgorithm("FaceRecognition");

	// Initialize templates
	if (argc == 1) return 0;
	
	br::Template queryA(argv[1]);

	


	//br::Template::toUniversalTemplate(target);



	//if (argv[1]="in")
	// Enroll templates
	queryA >> *transform;


	//transform.
	QString filename = argv[2];
	QFile file(filename);

	if (file.open(QIODevice::ReadWrite))
	{
	QDataStream stream(&file);
		stream << queryA;
}


	//QVariantMap datamap = target.file.localMetadata();

	//for(QVariantMap::const_iterator iter = datamap.begin(); iter != datamap.end(); ++iter) {                      qDebug() << "Keys Are: " << iter.key() << "Values Are: " << iter.value();                    }    float comparisonA = distance->compare(target, queryA);    printf("Genuine match score: %.3f\n", comparisonA);


	br::Context::finalize();
	//printf("end");
	//system("pause");
	return 0;
}
