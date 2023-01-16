#ifndef SAMPLECUSTENT_H
#define SAMPLECUSTENT_H
#pragma once
#include<vector>
using namespace std;

class SampleCustEnt : public AcDbEntity
{
public:
	ACRX_DECLARE_MEMBERS(SampleCustEnt);

protected:
	static Adesk::UInt32 kCurrentVersionNumber;

public:
	vector<AcDbObjectId> m_idsForDisp;
	vector<AcGePoint3d> pts;

	SampleCustEnt();
	//SampleCustEnt(AcGePoint3d cen, double rad);
	SampleCustEnt(const AcDbObjectId& id);
	virtual ~SampleCustEnt();

	
	AcGePoint3d getstartpt() const;
	AcGePoint3d getendpt() const;
	AcGePoint3d gettargetpt() const;
	Acad::ErrorStatus setstartpt(AcGePoint3d& pt);
	Acad::ErrorStatus settargetpt(AcGePoint3d& pt);
	Acad::ErrorStatus setendpt(AcGePoint3d& pt);

	AcGePoint3d getPointAt(unsigned int x) const;
	Acad::ErrorStatus setPointAt(unsigned int x, ZcGePoint3d& pt);
	AcGePoint3d getcenterpt() const;

	double getzoom() const;
	Acad::ErrorStatus setzoom(double x);

	double getangel() const;
	Acad::ErrorStatus setangle(double x);

	Acad::ErrorStatus subDeepClone(AcDbObject*    pOwner,
		AcDbObject*&   pClonedObject,
		AcDbIdMapping& idMap,
		Adesk::Boolean isPrimary) const;
	Acad::ErrorStatus subWblockClone(
		AcRxObject*    pOwner,
		AcDbObject*&   pClonedObject,
		AcDbIdMapping& idMap,
		Adesk::Boolean isPrimary) const;

	virtual Acad::ErrorStatus dwgOutFields(AcDbDwgFiler *pFiler) const;
	virtual Acad::ErrorStatus dwgInFields(AcDbDwgFiler *pFiler);
	virtual Acad::ErrorStatus dxfOutFields(AcDbDxfFiler *pFiler) const;
	virtual Acad::ErrorStatus dxfInFields(AcDbDxfFiler *pFiler);

	Acad::ErrorStatus subTransformBy(const ZcGeMatrix3d& xform);

	virtual Acad::ErrorStatus subGetOsnapPoints(
		AcDb::OsnapMode osnapMode,
		Adesk::GsMarker gsSelectionMark,
		const AcGePoint3d &pickPoint,
		const AcGePoint3d &lastPoint,
		const AcGeMatrix3d &viewXform,
		AcGePoint3dArray &snapPoints,
		AcDbIntArray &geomIds) const;

	virtual Acad::ErrorStatus subGetOsnapPoints(
		AcDb::OsnapMode osnapMode,
		Adesk::GsMarker gsSelectionMark,
		const AcGePoint3d &pickPoint,
		const AcGePoint3d &lastPoint,
		const AcGeMatrix3d &viewXform,
		AcGePoint3dArray &snapPoints,
		AcDbIntArray &geomIds,
		const AcGeMatrix3d &insertionMat) const;

	virtual Acad::ErrorStatus subGetGripPoints(AcGePoint3dArray &gripPoints, AcDbIntArray &osnapModes, AcDbIntArray &geomIds) const;
	virtual Acad::ErrorStatus subMoveGripPointsAt(const AcDbIntArray &indices, const AcGeVector3d &offset);
	virtual Acad::ErrorStatus subGetGripPoints(
		AcDbGripDataPtrArray &grips, const double curViewUnitSize, const int gripSize,
		const AcGeVector3d &curViewDir, const int bitflags) const;
	virtual Acad::ErrorStatus subMoveGripPointsAt(const AcDbVoidPtrArray &gripAppData, const AcGeVector3d &offset, const int bitflags);

	//----- AcDbEntity protocols
	//----- Graphics protocol
protected:
	virtual Adesk::Boolean subWorldDraw(AcGiWorldDraw *mode);
	virtual Adesk::UInt32 subSetAttributes(AcGiDrawableTraits *traits);

	//----- AcDbObject protocols

private:
	AcGePoint3d startpt;
	AcGePoint3d targetpt;
	AcGePoint3d endpt;
	AcDbObjectId m_srcId;
	double zooming;
	double angle;

};

#endif