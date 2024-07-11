	bool Open()
	{
		QFile file("C:/Work/C++/CAN/ProtocolMy/protocol1.main");
		QString main;
		if(file.exists())
		{
			if(file.open(QFile::ReadWrite))
			{
				main = file.readAll();
				file.close();
			}
			else return false;
		}
		else return false;

		return true;
	}