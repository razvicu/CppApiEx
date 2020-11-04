#include <QCoreApplication>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrl>

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	QUrl url = QUrl("https://jsonplaceholder.typicode.com/todos");
	QNetworkRequest request(url);

	QNetworkAccessManager manager{};
	QNetworkReply *reply = manager->get(request);

	QObject::connect(reply, &QNetworkReply::finished, [=]() {
		if (reply->error()) {
			qDebug() << "Error reading data";
			return;
		}
		QByteArray response = reply->readAll();
		QJsonDocument doc = QJsonDocument::fromJson(response);
		QJsonArray arr = doc.array();

		// iterate over all elements of the received array
		for(auto item : arr) {
			QJsonObject obj = item.toObject();
			// iterate over all object properties
			for (auto key : obj.keys()) {
				qDebug() << key << " ";
				auto value = obj.value(key);

				if (value.isString()) {
					qDebug() << value.toString() << "\n";
				} else if (value.isDouble()) {
					qDebug() << value.toDouble() << "\n";
				} else if (value.isBool()) {
					qDebug() << value.toBool() << "\n";
				}
			}
		}
	});

	return a.exec();
}
