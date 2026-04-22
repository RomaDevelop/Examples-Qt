auto labelFrom = CreatePreviewLabel();
auto labelTo = CreatePreviewLabel();
labelFrom->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Preferred); // и не заползают
labelTo->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Preferred);
table->setCellWidget(row, 1, labelFrom);
table->setCellWidget(row, 2, labelTo);