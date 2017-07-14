set(EXTERNALPACKAGES ${PROJECT_SOURCE_DIR}/externalpackages)
#############
# qt spinner widget
#include_directories(${EXTERNALPACKAGES}/qspinner)
set(QSpinner_SOURCES
	${EXTERNALPACKAGES}/qspinner/waitingspinnerwidget.h 
	${EXTERNALPACKAGES}/qspinner/waitingspinnerwidget.cpp
	PARENT_SCOPE
)
