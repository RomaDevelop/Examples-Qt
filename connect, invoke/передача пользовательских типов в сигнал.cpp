struct SearchResult
{
	IConfigItem *configItemPtr {};
	int fieldIndex = -1;
	int indexInField = -1;
	int length = -1;
};

void SignalSearchResultDoubleClicked(SearchResult searchResult);
// работает из коробки без фокусов