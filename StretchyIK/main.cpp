#include<maya/MFnPlugin.h>

#include"StretchyIK.h"


MStatus initializePlugin(MObject plugin) {
	MStatus status;
	MFnPlugin pluginFn(plugin, "Matthew Pierce", "1.0", "Any", &status);CHECK_MSTATUS_AND_RETURN_IT(status);
	CHECK_MSTATUS_AND_RETURN_IT(pluginFn.registerNode(
		"StretchyIK",
		StretchyIK::typeId,
		&StretchyIK::creator,
		&StretchyIK::initialize
	));
	return MS::kSuccess;
}

MStatus uninitializePlugin(MObject plugin) {
	MFnPlugin pluginFn(plugin);
	CHECK_MSTATUS_AND_RETURN_IT(pluginFn.deregisterNode(StretchyIK::typeId));

	return MS::kSuccess;
}