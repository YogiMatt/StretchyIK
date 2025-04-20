#pragma once

#include"StretchyIK.h"


double lerp(double a, double b, double t) {
	return a + (b - a) * t;
}

MTypeId StretchyIK::typeId = 0x8005;

//IK Chain info

MObject StretchyIK::inRootMatrixAttr;
MObject StretchyIK::inPoleVectorMatrixAttr;
MObject StretchyIK::inControlMatrixAttr;
MObject StretchyIK::inUpperLengthAttr;
MObject StretchyIK::inLowerLengthAttr;
MObject StretchyIK::inGlobalScaleAttr;

//Features
MObject StretchyIK::inSlideAttr;
MObject StretchyIK::inStretchAttr;
MObject StretchyIK::inPoleVectorLockAttr;

//Outputs

MObject StretchyIK::outUpperLengthAttr;
MObject StretchyIK::outLowerLengthAttr;

void* StretchyIK::creator(){ return new StretchyIK;}

MStatus StretchyIK::initialize() {
	MStatus status;
	MFnMatrixAttribute matFn;
	MFnUnitAttribute unitFn;
	MFnNumericAttribute numericFn;


	//IK Chain info

	inRootMatrixAttr = matFn.create("inRoot", "inRoot,", MFnMatrixAttribute::kDouble, &status); CHECK_MSTATUS_AND_RETURN_IT(status);
	status = addAttribute(inRootMatrixAttr);CHECK_MSTATUS_AND_RETURN_IT(status);

	inPoleVectorMatrixAttr = matFn.create("inPoleVector", "inPoleVector", MFnMatrixAttribute::kDouble, &status);CHECK_MSTATUS_AND_RETURN_IT(status);
	status = addAttribute(inPoleVectorMatrixAttr);CHECK_MSTATUS_AND_RETURN_IT(status);

	inControlMatrixAttr = matFn.create("inControl", "inControl", MFnMatrixAttribute::kDouble, &status);CHECK_MSTATUS_AND_RETURN_IT(status);
	status = addAttribute(inControlMatrixAttr);CHECK_MSTATUS_AND_RETURN_IT(status);

	inUpperLengthAttr = unitFn.create("inUpperLength", "inUpperLength", MFnUnitAttribute::kDistance, 0.0, &status);CHECK_MSTATUS_AND_RETURN_IT(status);
	status = unitFn.setMin(0.0);CHECK_MSTATUS_AND_RETURN_IT(status);
	status = addAttribute(inUpperLengthAttr);CHECK_MSTATUS_AND_RETURN_IT(status);

	inLowerLengthAttr = unitFn.create("inLowerLength", "inLowerLength", MFnUnitAttribute::kDistance, 0.0, &status);CHECK_MSTATUS_AND_RETURN_IT(status);
	status = unitFn.setMin(0.0);CHECK_MSTATUS_AND_RETURN_IT(status);
	status = addAttribute(inLowerLengthAttr);CHECK_MSTATUS_AND_RETURN_IT(status);

	inGlobalScaleAttr = numericFn.create("inGlobalScale", "inGlobalScale", MFnNumericData::kDouble, 0.0, &status);CHECK_MSTATUS_AND_RETURN_IT(status);
	status = numericFn.setMin(0.0);CHECK_MSTATUS_AND_RETURN_IT(status);
	status = addAttribute(inGlobalScaleAttr);CHECK_MSTATUS_AND_RETURN_IT(status);

	inSlideAttr = numericFn.create("inSlide", "inSlide", MFnNumericData::kDouble, 0.0, &status);CHECK_MSTATUS_AND_RETURN_IT(status);
	status = numericFn.setMin(-1.0);CHECK_MSTATUS_AND_RETURN_IT(status);
	status = numericFn.setMax(1.0);CHECK_MSTATUS_AND_RETURN_IT(status);
	status = addAttribute(inSlideAttr);CHECK_MSTATUS_AND_RETURN_IT(status);

	inStretchAttr = numericFn.create("inStretch", "inStretch", MFnNumericData::kDouble, 0.0, &status);CHECK_MSTATUS_AND_RETURN_IT(status);
	status = numericFn.setMin(0.0);CHECK_MSTATUS_AND_RETURN_IT(status);
	status = numericFn.setMax(1.0);CHECK_MSTATUS_AND_RETURN_IT(status);
	status = addAttribute(inStretchAttr);CHECK_MSTATUS_AND_RETURN_IT(status);

	inPoleVectorLockAttr = numericFn.create("inPoleVectorLock", "inPoleVectorLock", MFnNumericData::kDouble, 0.0, &status);CHECK_MSTATUS_AND_RETURN_IT(status);
	status = numericFn.setMin(0.0);CHECK_MSTATUS_AND_RETURN_IT(status);
	status = numericFn.setMax(1.0);CHECK_MSTATUS_AND_RETURN_IT(status);
	status = addAttribute(inPoleVectorLockAttr);CHECK_MSTATUS_AND_RETURN_IT(status);

	outUpperLengthAttr = numericFn.create("outUpperLength", "outUpperLength", MFnNumericData::kDouble, 0.0, &status);CHECK_MSTATUS_AND_RETURN_IT(status);
	status = addAttribute(outUpperLengthAttr);CHECK_MSTATUS_AND_RETURN_IT(status);

	outLowerLengthAttr = numericFn.create("outLowerLength", "outLowerLength", MFnNumericData::kDouble, 0.0, &status);CHECK_MSTATUS_AND_RETURN_IT(status);
	status = addAttribute(outLowerLengthAttr);CHECK_MSTATUS_AND_RETURN_IT(status);

	// IK Chain info

	status = attributeAffects(inRootMatrixAttr, outUpperLengthAttr);CHECK_MSTATUS_AND_RETURN_IT(status);
	status = attributeAffects(inRootMatrixAttr, outLowerLengthAttr);CHECK_MSTATUS_AND_RETURN_IT(status);

	status = attributeAffects(inPoleVectorMatrixAttr, outUpperLengthAttr);CHECK_MSTATUS_AND_RETURN_IT(status);
	status = attributeAffects(inPoleVectorMatrixAttr, outLowerLengthAttr);CHECK_MSTATUS_AND_RETURN_IT(status);

	status = attributeAffects(inControlMatrixAttr, outUpperLengthAttr);CHECK_MSTATUS_AND_RETURN_IT(status);
	status = attributeAffects(inControlMatrixAttr, outLowerLengthAttr);CHECK_MSTATUS_AND_RETURN_IT(status);

	status = attributeAffects(inUpperLengthAttr, outUpperLengthAttr);CHECK_MSTATUS_AND_RETURN_IT(status);
	status = attributeAffects(inUpperLengthAttr, outLowerLengthAttr);CHECK_MSTATUS_AND_RETURN_IT(status);

	status = attributeAffects(inLowerLengthAttr, outUpperLengthAttr);CHECK_MSTATUS_AND_RETURN_IT(status);
	status = attributeAffects(inLowerLengthAttr, outLowerLengthAttr);CHECK_MSTATUS_AND_RETURN_IT(status);

	status = attributeAffects(inGlobalScaleAttr, outUpperLengthAttr);CHECK_MSTATUS_AND_RETURN_IT(status);
	status = attributeAffects(inGlobalScaleAttr, outLowerLengthAttr);CHECK_MSTATUS_AND_RETURN_IT(status);

	/*status = attributeAffects(inControlMatrixAttr, outUpperLengthAttr);CHECK_MSTATUS_AND_RETURN_IT(status);
	status = attributeAffects(inControlMatrixAttr, outLowerLengthAttr);CHECK_MSTATUS_AND_RETURN_IT(status);*/

	// Features

	status = attributeAffects(inSlideAttr, outUpperLengthAttr);CHECK_MSTATUS_AND_RETURN_IT(status);
	status = attributeAffects(inSlideAttr, outLowerLengthAttr);CHECK_MSTATUS_AND_RETURN_IT(status);

	status = attributeAffects(inStretchAttr, outUpperLengthAttr);CHECK_MSTATUS_AND_RETURN_IT(status);
	status = attributeAffects(inStretchAttr, outLowerLengthAttr);CHECK_MSTATUS_AND_RETURN_IT(status);

	status = attributeAffects(inPoleVectorLockAttr, outUpperLengthAttr);CHECK_MSTATUS_AND_RETURN_IT(status);
	status = attributeAffects(inPoleVectorLockAttr, outLowerLengthAttr);CHECK_MSTATUS_AND_RETURN_IT(status);

	return status;
}

MStatus StretchyIK::compute(const MPlug& p, MDataBlock& b){
	if (p != outUpperLengthAttr
		&& p != outLowerLengthAttr)
		return MS::kInvalidParameter;

	//Get the chain length

	double upperLength = b.inputValue(inUpperLengthAttr).asDistance().asCentimeters();
	double lowerLength = b.inputValue(inLowerLengthAttr).asDistance().asCentimeters();

	// Make sure the chain length matches
	double chainLength = upperLength + lowerLength;

	//Input reading//
	//get the position of the incoming matrices
	// this gets the matrix

	MMatrix rootM = b.inputValue(inRootMatrixAttr).asMatrix();
	MMatrix pvM = b.inputValue(inPoleVectorMatrixAttr).asMatrix();
	MMatrix ctrlM = b.inputValue(inControlMatrixAttr).asMatrix();

	// This gets the workd space translation from the matrix

	MVector root(rootM[3]);
	MVector pv(pvM[3]);
	MVector ctrl(ctrlM[3]); // this is the Ik handle

	double globalScale = b.inputValue(inGlobalScaleAttr).asDouble();
	if (globalScale < 0.0001) globalScale = 0.00001;
	root /= globalScale;
	pv /= globalScale;
	ctrl /= globalScale;


	//Slide

	double slide = b.inputValue(inSlideAttr).asDouble();

	if (slide < -0.999) slide = -0.999;
	if (slide > 0.999) slide = 0.999;

	if (slide < 0.0) {
		upperLength = lerp(upperLength, 0.0, -slide);
		lowerLength = lerp(lowerLength, chainLength, -slide);

	}
	else
	{
		upperLength = lerp(upperLength, chainLength, slide);
		lowerLength = lerp(lowerLength, 0.0, slide);
	}

	//Stretch

	MVector ikhDelta = ctrl - root;
	double desiredChainLength = ikhDelta.length();
	double stretch = b.inputValue(inStretchAttr).asDouble();
	double scaleFactor = 1.0;
	if (desiredChainLength > chainLength) {
		scaleFactor = desiredChainLength / chainLength;
		scaleFactor = lerp(1.0, scaleFactor, stretch);
		upperLength *= scaleFactor;
		lowerLength *= scaleFactor;
	}

	// Pole Vector Lock

	double poleVectorLock = b.inputValue(inPoleVectorLockAttr).asDouble();
	if (poleVectorLock > 0.0) {
		double desiredUpperLength = (pv - root).length();
		double desiredLowerLength = (ctrl - pv).length();

		upperLength = lerp(upperLength, desiredUpperLength, poleVectorLock);
		lowerLength = lerp(lowerLength, desiredLowerLength, poleVectorLock);
	}

	//Set Out Puts

	b.outputValue(outUpperLengthAttr).setDouble(upperLength);
	b.outputValue(outLowerLengthAttr).setDouble(lowerLength);
	b.setClean(outUpperLengthAttr);
	b.setClean(outLowerLengthAttr);

	return MS::kSuccess;


}



