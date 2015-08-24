#include "OnlineTileLoader.h"
#include "TileInfo.h"

#include <QDebug>
#include <QImageReader>
#include <QNetworkReply>
#include "DownloadTileRequest.h"

OnlineTileLoader::OnlineTileLoader()
{
	// Create the network access manager used to fetch tiles from server
	networkAccesManager = new QNetworkAccessManager(this);

	QObject::connect(
		networkAccesManager, 
		SIGNAL(finished(QNetworkReply*)),
		this, 
		SLOT(networkReplyReady(QNetworkReply*))
	);
}

OnlineTileLoader::~OnlineTileLoader()
{
	delete networkAccesManager;
}

void OnlineTileLoader::loadTile(TileInfo info)
{
	// Metadata Object
	DownloadTileRequest* request = tileRequestFactory.createTileRequest(info);

    qDebug() << request->getRequestUrl() << " ";
	QUrl url(request->getRequestUrl());
	// Create the request obj
    QNetworkRequest networkRequest(url);
	networkRequest.setOriginatingObject(request);
    networkRequest.setRawHeader("User-Agent", "Mozilla Firefox");
		
	// Send async request
	QNetworkReply* reply = networkAccesManager->get(networkRequest);	
}

void OnlineTileLoader::networkReplyReady(QNetworkReply* reply)
{
    qDebug() << reply->error() << " ";
    qDebug() << reply->attribute(QNetworkRequest::HttpStatusCodeAttribute) << " ";
	// Error check
	if (reply->error() == QNetworkReply::NoError)
	{
		// Creating QImage from the reply
		QImageReader imageReader(reply);
		QImage picture = imageReader.read();

		// Create request object
		DownloadTileRequest* downloadTileRequest = (DownloadTileRequest*)(reply->request().originatingObject());

		if (downloadTileRequest != NULL)
		{		
			// Create the tile obj with received informations
			Tile loadedTile(downloadTileRequest->getTileInfo(), picture);
			// Fire the response
			emit onlineTileLoaded(loadedTile);		
		}
	}	
	// indicate "reply" need to be deleted
	reply->deleteLater();
}
