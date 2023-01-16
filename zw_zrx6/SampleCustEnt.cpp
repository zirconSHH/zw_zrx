// (C) Copyright 2002-2007 by Autodesk, Inc. 
//
// Permission to use, copy, modify, and distribute this software in
// object code form for any purpose and without fee is hereby granted, 
// provided that the above copyright notice appears in all copies and 
// that both that copyright notice and the limited warranty and
// restricted rights notice below appear in all supporting 
// documentation.
//
// AUTODESK PROVIDES THIS PROGRAM "AS IS" AND WITH ALL FAULTS. 
// AUTODESK SPECIFICALLY DISCLAIMS ANY IMPLIED WARRANTY OF
// MERCHANTABILITY OR FITNESS FOR A PARTICULAR USE.  AUTODESK, INC. 
// DOES NOT WARRANT THAT THE OPERATION OF THE PROGRAM WILL BE
// UNINTERRUPTED OR ERROR FREE.
//
// Use, duplication, or disclosure by the U.S. Government is subject to 
// restrictions set forth in FAR 52.227-19 (Commercial Computer
// Software - Restricted Rights) and DFAR 252.227-7013(c)(1)(ii)
// (Rights in Technical Data and Computer Software), as applicable.
//

//-----------------------------------------------------------------------------
//----- SampleCustEnt.cpp : Implementation of SampleCustEnt
//-----------------------------------------------------------------------------
#include "pch.h"
#include "tchar.h"
#include "acadstrc.h"
#include "dbproxy.h"
#include "rxboiler.h"
#include "dbapserv.h"
#include "dbidmap.h"
#include "dbcfilrs.h"

#include "SampleCustEnt.h"

//-----------------------------------------------------------------------------
Adesk::UInt32 SampleCustEnt::kCurrentVersionNumber =1 ;

//-----------------------------------------------------------------------------
ACRX_DXF_DEFINE_MEMBERS (
	SampleCustEnt, AcDbEntity,
	AcDb::kDHL_CURRENT, AcDb::kMReleaseCurrent, 
	AcDbProxyEntity::kNoOperation, SAMPLECUSTENT,
ARXPROJECT1APP
|Product Desc:     A description for your object
|Company:          Your company name
|WEB Address:      Your company WEB site address
)

//-----------------------------------------------------------------------------
SampleCustEnt::SampleCustEnt () : AcDbEntity () {
}

SampleCustEnt::SampleCustEnt(const AcDbObjectId& id) : AcDbEntity() {
	m_srcId = id;
}

SampleCustEnt::~SampleCustEnt () {
}




//-----------------------------------------------------------------------------
//----- AcDbObject protocols
//- Dwg Filing protocol
Acad::ErrorStatus SampleCustEnt::dwgOutFields (AcDbDwgFiler *pFiler) const {
	assertReadEnabled () ;
	//----- Save parent class information first.
	Acad::ErrorStatus es =AcDbEntity::dwgOutFields (pFiler) ;
	if ( es != Acad::eOk )
		return (es) ;
	//----- Object version number needs to be saved first
	if ( (es =pFiler->writeUInt32 (SampleCustEnt::kCurrentVersionNumber)) != Acad::eOk )
		return (es) ;
	//----- Output params
	pFiler->writePoint3d(startpt);
	pFiler->writePoint3d(endpt);
	pFiler->writePoint3d(targetpt);
	AcDbHardPointerId id(m_srcId);
	pFiler->writeHardPointerId(id);

	return (pFiler->filerStatus ()) ;
}
Acad::ErrorStatus SampleCustEnt::dwgInFields (AcDbDwgFiler *pFiler) {
	assertWriteEnabled () ;
	//----- Read parent class information first.
	Acad::ErrorStatus es =AcDbEntity::dwgInFields (pFiler) ;
	if ( es != Acad::eOk )
		return (es) ;
	//----- Object version number needs to be read first
	Adesk::UInt32 version =0 ;
	if ( (es =pFiler->readUInt32 (&version)) != Acad::eOk )
		return (es) ;
	if ( version > SampleCustEnt::kCurrentVersionNumber )
		return (Acad::eMakeMeProxy) ;
	if ( version < SampleCustEnt::kCurrentVersionNumber )
		return (Acad::eMakeMeProxy) ;
	//----- Read params
	pFiler->readPoint3d(&startpt);
	pFiler->readPoint3d(&endpt);
	pFiler->readPoint3d(&targetpt);
	AcDbHardPointerId id;
	pFiler->readHardPointerId(&id);
	m_srcId = id;

	return (pFiler->filerStatus ()) ;
}

//- Dxf Filing protocol
Acad::ErrorStatus SampleCustEnt::dxfOutFields (AcDbDxfFiler *pFiler) const {
	assertReadEnabled () ;
	//----- Save parent class information first.
	Acad::ErrorStatus es =AcDbEntity::dxfOutFields (pFiler) ;
	if ( es != Acad::eOk )
		return (es) ;
	es =pFiler->writeItem (AcDb::kDxfSubclass, _T("SampleCustEnt")) ;
	if ( es != Acad::eOk )
		return (es) ;
	//----- Object version number needs to be saved first
	if ( (es =pFiler->writeUInt32 (AcDb::kDxfInt32, SampleCustEnt::kCurrentVersionNumber)) != Acad::eOk )
		return (es) ;
	//----- Output params
	//.....

	return (pFiler->filerStatus ()) ;
}

Acad::ErrorStatus SampleCustEnt::dxfInFields (AcDbDxfFiler *pFiler) {
	assertWriteEnabled () ;
	//----- Read parent class information first.
	Acad::ErrorStatus es =AcDbEntity::dxfInFields (pFiler) ;
	if ( es != Acad::eOk || !pFiler->atSubclassData (_T("SampleCustEnt")) )
		return (pFiler->filerStatus ()) ;
	//----- Object version number needs to be read first
	struct resbuf rb ;
	pFiler->readItem (&rb) ;
	if ( rb.restype != AcDb::kDxfInt32 ) {
		pFiler->pushBackItem () ;
		pFiler->setError (Acad::eInvalidDxfCode, _T("\nError: expected group code %d (version #)"), AcDb::kDxfInt32) ;
		return (pFiler->filerStatus ()) ;
	}
	Adesk::UInt32 version =(Adesk::UInt32)rb.resval.rlong ;
	if ( version > SampleCustEnt::kCurrentVersionNumber )
		return (Acad::eMakeMeProxy) ;
	//- Uncomment the 2 following lines if your current object implementation cannot
	//- support previous version of that object.
	//if ( version < SampleCustEnt::kCurrentVersionNumber )
	//	return (Acad::eMakeMeProxy) ;
	//----- Read params in non order dependant manner
	while ( es == Acad::eOk && (es =pFiler->readResBuf (&rb)) == Acad::eOk ) {
		switch ( rb.restype ) {
			//----- Read params by looking at their DXF code (example below)
			case AcDb::kDxfXCoord:
				break ;

			default:
				//----- An unrecognized group. Push it back so that the subclass can read it again.
				pFiler->pushBackItem () ;
				es =Acad::eEndOfFile ;
				break ;
		}
	}
	//----- At this point the es variable must contain eEndOfFile
	//----- - either from readResBuf() or from pushback. If not,
	//----- it indicates that an error happened and we should
	//----- return immediately.
	if ( es != Acad::eEndOfFile )
		return (Acad::eInvalidResBuf) ;

	return (pFiler->filerStatus ()) ;
}

//-----------------------------------------------------------------------------
//----- AcDbEntity protocols


Adesk::UInt32 SampleCustEnt::subSetAttributes (AcGiDrawableTraits *traits) {
	assertReadEnabled () ;
	return (AcDbEntity::subSetAttributes (traits)) ;
}

Acad::ErrorStatus SampleCustEnt::subTransformBy(const ZcGeMatrix3d& xform)
{
	startpt.transformBy(xform);
	endpt.transformBy(xform);

	return Acad::eOk;
}

Acad::ErrorStatus SampleCustEnt::setstartpt(AcGePoint3d& pt)
{
	assertWriteEnabled();
	startpt = pt;
	return Acad::eOk;
}

Acad::ErrorStatus SampleCustEnt::setendpt(AcGePoint3d & pt)
{
	assertWriteEnabled();
	endpt = pt;
	return Acad::eOk;
}

double SampleCustEnt::getzoom() const
{
	return zooming;
}

Acad::ErrorStatus SampleCustEnt::setzoom(double x)
{
	zooming = x;
	return Acad::eOk;
}

double SampleCustEnt::getangel() const
{
	return angle;
}

Acad::ErrorStatus SampleCustEnt::setangle(double x)
{
	angle = x;
	return Acad::eOk;
}

Acad::ErrorStatus SampleCustEnt::settargetpt(AcGePoint3d & pt)
{
	assertWriteEnabled();
	targetpt = pt;
	return Acad::eOk;
}

AcGePoint3d SampleCustEnt::getstartpt() const
{
	assertReadEnabled();
	return startpt;
}

AcGePoint3d SampleCustEnt::getendpt() const
{
	assertReadEnabled();
	return endpt;
}

AcGePoint3d SampleCustEnt::gettargetpt() const
{
	assertReadEnabled();
	return targetpt;
}

AcGePoint3d SampleCustEnt::getPointAt(unsigned int x) const
{
	return pts[x];
}

Acad::ErrorStatus SampleCustEnt::setPointAt(unsigned int x, ZcGePoint3d& pt)
{
	pts[x] = pt;
	return Acad::ErrorStatus();
}

AcGePoint3d SampleCustEnt::getcenterpt() const
{
	AcGePoint3d centerpt;
	for (int i = 0; i < pts.size(); i++)
	{
		centerpt[0] = (centerpt[0] * i + pts[i][0]) / (i + 1);
		centerpt[1] = (centerpt[1] * i + pts[i][1]) / (i + 1);
		centerpt[2] = (centerpt[2] * i + pts[i][2]) / (i + 1);
	}
	return centerpt;
}

Acad::ErrorStatus SampleCustEnt::subGetOsnapPoints(
	AcDb::OsnapMode osnapMode,
	Adesk::GsMarker gsSelectionMark,
	const AcGePoint3d &pickPoint,
	const AcGePoint3d &lastPoint,
	const AcGeMatrix3d &viewXform,
	AcGePoint3dArray &snapPoints,
	AcDbIntArray &geomIds) const {
	assertReadEnabled();
	return (AcDbEntity::subGetOsnapPoints(osnapMode, gsSelectionMark, pickPoint, lastPoint, viewXform, snapPoints, geomIds));
}

Acad::ErrorStatus SampleCustEnt::subGetOsnapPoints(
	AcDb::OsnapMode osnapMode,
	Adesk::GsMarker gsSelectionMark,
	const AcGePoint3d &pickPoint,
	const AcGePoint3d &lastPoint,
	const AcGeMatrix3d &viewXform,
	AcGePoint3dArray &snapPoints,
	AcDbIntArray &geomIds,
	const AcGeMatrix3d &insertionMat) const {
	assertReadEnabled();
	return (AcDbEntity::subGetOsnapPoints(osnapMode, gsSelectionMark, pickPoint, lastPoint, viewXform, snapPoints, geomIds, insertionMat));
}

enum PartialUndoCode { kRadius };

Adesk::Boolean SampleCustEnt::subWorldDraw(AcGiWorldDraw *mode) {
	assertReadEnabled();
	AcGiWorldGeometry * pGeom = &mode->geometry();
	//myTransform()�Ǵӿ鶨�������ϵ(ģ������ϵ)�������õ�ת������
	
	AcGeMatrix3d zoommatrix = AcGeMatrix3d::scaling(zooming, getcenterpt());
	AcGeVector3d rotvec = AcGeVector3d(0, 0, 1);
	AcGeMatrix3d rotmatrix = rotmatrix.setToRotation(angle, rotvec, getcenterpt());
	AcGeMatrix3d movematrix = AcGeMatrix3d::translation(targetpt - startpt);
	movematrix *= zoommatrix * rotmatrix;

	AcGiClipBoundary cb;
	cb.m_bDrawBoundary = true;
	cb.m_vNormal = AcGeVector3d::kZAxis;
	cb.m_ptPoint = AcGePoint3d::kOrigin;
	//append�����������Σ����������������
	for (int i = 0; i < pts.size(); i++)
	{
		cb.m_aptPoints.append(AcGePoint2d(pts[i][0], pts[i][1]));
	}

	//�����������ü�����ϵ��ģ������ϵһ��
	cb.m_xToClipSpace.setToIdentity();
	cb.m_xInverseBlockRefXForm.setToIdentity();
	//�������û����ǰ�ü��ͺ�ü�
	cb.m_bClippingBack = cb.m_bClippingFront = false;
	cb.m_dFrontClipZ = cb.m_dBackClipZ = 0.;

	mode->geometry().pushModelTransform(movematrix);
	Adesk::Boolean bPopClipBoundary = pGeom->pushClipBoundary(&cb);	for (auto i = 0; i < m_idsForDisp.size(); i++)	{		AcDbEntity* pEnt = nullptr;		acdbOpenAcDbEntity(pEnt, m_idsForDisp[i], AcDb::kForWrite);		if (pEnt)		{			mode->geometry().draw(pEnt);			pEnt->close();		}	}	mode->geometry().popModelTransform();



	if (bPopClipBoundary)	{		pGeom->popClipBoundary();	}
	return (AcDbEntity::subWorldDraw(mode));
}

Acad::ErrorStatus SampleCustEnt::subGetGripPoints(AcGePoint3dArray& gripPoints, AcDbIntArray & osnapModes, AcDbIntArray & geomIds) const {
	assertReadEnabled();

	AcGeMatrix3d zoommatrix = AcGeMatrix3d::scaling(zooming, getcenterpt());
	AcGeVector3d rotvec = AcGeVector3d(0, 0, 1);
	AcGeMatrix3d rotmatrix = rotmatrix.setToRotation(angle, rotvec, getcenterpt());
	AcGeMatrix3d movematrix = AcGeMatrix3d::translation(targetpt - startpt);
	movematrix *= zoommatrix * rotmatrix;

	gripPoints.append(getcenterpt().transformBy(movematrix));

	for (int i = 0; i < pts.size(); i++)
	{
		AcGePoint3d edge = pts[i];
		gripPoints.append(edge.transformBy(movematrix));
	}
	return Acad::eOk;
}
Acad::ErrorStatus SampleCustEnt::subMoveGripPointsAt(const AcDbIntArray & indices, const AcGeVector3d& offset) {
	assertWriteEnabled();
	switch (indices[0]) {
	case(0):
		targetpt += offset;
		break;
	case(1):
		targetpt += offset;
		break;
	case(2):
		targetpt += offset;
		break;
	case(3):
		targetpt += offset;
		break;
	case(4):
		targetpt += offset;
		break;
	}
	return Acad::eOk;
}

Acad::ErrorStatus SampleCustEnt::subGetGripPoints(
	AcDbGripDataPtrArray &grips, const double curViewUnitSize, const int gripSize,
	const AcGeVector3d &curViewDir, const int bitflags
) const {
	assertReadEnabled();

	//----- If you return eNotImplemented here, that will force AutoCAD to call
	//----- the older getGripPoints() implementation. The call below may return
	//----- eNotImplemented depending of your base class.
	return (AcDbEntity::subGetGripPoints(grips, curViewUnitSize, gripSize, curViewDir, bitflags));
}

Acad::ErrorStatus SampleCustEnt::subMoveGripPointsAt(const AcDbVoidPtrArray &gripAppData, const AcGeVector3d &offset,
	const int bitflags
) {
	assertWriteEnabled();

	//----- If you return eNotImplemented here, that will force AutoCAD to call
	//----- the older getGripPoints() implementation. The call below may return
	//----- eNotImplemented depending of your base class.
	return (AcDbEntity::subMoveGripPointsAt(gripAppData, offset, bitflags));
}

Acad::ErrorStatus
SampleCustEnt::subDeepClone(AcDbObject*    pOwner,
	AcDbObject*&   pClonedObject,
	AcDbIdMapping& idMap,
	Adesk::Boolean isPrimary) const
{
	//��������Ӧ�ڴ�������ʱ�����ΪNULL�������Է���һ������Ҫ���ÿ�
	//������һû���Ƴɹ��ó�ȥ����Ұָ��
	pClonedObject = NULL;

	//������ʵ���Ѿ�������Id Map�����Ѿ������ƹ��ˣ���Id Map���Ѿ�������ɶԵ�Id�ˣ���
	//�Ͳ����ٸ����ˣ�ֱ�ӷ���
	//˼����ʲô����»ᷢ�������£�
	bool isPrim = false;
	if (isPrimary)//isPrimary��ʾ��ǰ�����ƵĶ����Ǳ��������ƵĻ�����Ϊ���й�ϵ�������Ƶ�
		isPrim = true;
	AcDbIdPair idPair(objectId(), (AcDbObjectId)NULL,
		false, isPrim);
	if (idMap.compute(idPair) && (idPair.value() != NULL))
		return Acad::eOk;

	//����һ��������ͬ�Ķ���
	auto *pClone = (SampleCustEnt*)isA()->create();
	if (pClone != NULL)
		pClonedObject = pClone;    //������Ǹ��Ƴ����Ķ��󣬿����ȴ浽����ֵ��
	else
		return Acad::eOutOfMemory;

	AcDbDeepCloneFiler filer;
	dwgOut(&filer);//ͨ��dwgOut��ȡ�����������
	filer.seek(0L, AcDb::kSeekFromStart);//���������ļ���ָ�룬���������dwgIn
	pClone->dwgIn(&filer);

	//����Ҫ����owner�����������
	//1. ���owner�ǿ���¼���Ǿ�ֱ�ӵ���appendAcDbEntity�ӽ�ȥ
	//2. ���owner�Ǵʵ䣬��ʹ��setAt�ӵ��ʵ���������û�����֣�
	//3. �����ǰ��������Ϊ���ù�ϵ�������Ƶģ���ʹ��addAcDbObject()
	//�����ӵ�owner�����ݿ��ﲢֱ����������owner
	bool bOwnerXlated = false;//��ʾowner��id�Ƿ��Ѿ�ת��
	if (isPrimary)
	{
		AcDbBlockTableRecord *pBTR =
			AcDbBlockTableRecord::cast(pOwner);
		if (pBTR != NULL)
		{
			pBTR->appendAcDbEntity(pClone);
			bOwnerXlated = true;
		}
		else
		{//����������������֧��ʵ�ǲ����ܽ����ģ�����ֻ���ݴ�
			pOwner->database()->addAcDbObject(pClone);
		}
	}
	else {
		pOwner->database()->addAcDbObject(pClone);
		pClone->setOwnerId(pOwner->objectId());
		bOwnerXlated = true;
	}


	//ÿһ����deepclone�����ﴴ���Ķ���Ҫ�ڼ���Id Mapǰ����setAcDbObjectIdsInFlux()����
	pClone->setAcDbObjectIdsInFlux();
	pClone->disableUndoRecording(true);//pClone�����Ѿ������ݿ��ͨ�������ʽ���Խ��õ�����undo


	//��Դ����͸��ƶ���ճ�һ�ԣ��ŵ�Id Map��
	idPair.setValue(pClonedObject->objectId());
	idPair.setIsCloned(Adesk::kTrue);
	idPair.setIsOwnerXlated(bOwnerXlated);
	idMap.assign(idPair);

	//����Դ��������й�ϵ���������ǵ�deepClone����
	AcDbObjectId id;
	while (filer.getNextOwnedObject(id)) {

		AcDbObject *pSubObject;
		AcDbObject *pClonedSubObject;

		//���й�ϵ�Ķ���id��һ��������Ч�ģ���Ҫ�����
		if (id == NULL)
			continue;

		//ע����Ϊ��Щ�������������й�ϵ�������Ƶģ�����deepClone�����һ������(isPrimary)��Ҫ��Ϊfalse
		acdbOpenAcDbObject(pSubObject, id, AcDb::kForRead);
		pClonedSubObject = NULL;
		pSubObject->deepClone(pClonedObject,
			pClonedSubObject,
			idMap, Adesk::kFalse);

		//��ĳ���������(����ĳЩ����µ�Ԥ��)������ʵ����ֻ�����ݡ��ƶ�����
		//pSubObject��pClonedSubObject��ָ��ͬһ���������ʱ��Ͳ���close pSubObject��
		if (pSubObject != pClonedSubObject)
			pSubObject->close();

		//����������ʧ��pClonedSubObject�ͻ��ǿ�ָ�룬��Ҫ���
		if (pClonedSubObject != NULL)
			pClonedSubObject->close();
	}

	//ע���ʱpClonedObject��û�б��رյģ����ɵ�����������
	return Acad::eOk;
}

Acad::ErrorStatus SampleCustEnt::subWblockClone(
	AcRxObject*    pOwner,
	AcDbObject*&   pClonedObject,
	AcDbIdMapping& idMap,
	Adesk::Boolean isPrimary) const
{
	//�ǵ��Ȱѷ���ֵ�ÿ�
	pClonedObject = NULL;

	//���Դ���ݿ��Ŀ�����ݿ���ͬһ��������ʡ�Դ󲿷ֲ��裬ֱ�ӵ��û����wblockClone�Ϳ�����
	AcDbDatabase *pDest, *pOrig;
	idMap.destDb(pDest);
	idMap.origDb(pOrig);
	if (pDest == pOrig)
		return AcDbEntity::wblockClone(pOwner, pClonedObject,
			idMap, isPrimary);

	//��������ڽ���xbind����������xbindֻ����ģ�Ϳռ�Ķ������Դ������ͼֽ�ռ䣬��ֱ�ӷ���
	AcDbObjectId pspace;
	AcDbBlockTable *pTable;
	database()->getSymbolTable(pTable, AcDb::kForRead);
	pTable->getAt(ACDB_PAPER_SPACE, pspace);
	pTable->close();
	if (idMap.deepCloneContext() == AcDb::kDcXrefBind
		&& ownerId() == pspace)
		return Acad::eOk;

	//���Դ�����Ѿ������ƹ��ˣ�ֱ�ӷ���
	bool isPrim = false;
	if (isPrimary)
		isPrim = true;
	AcDbIdPair idPair(objectId(), (AcDbObjectId)NULL,
		false, isPrim);
	if (idMap.compute(idPair) && (idPair.value() != NULL))
		return Acad::eOk;

	//Դ�����owner�п��������ݿ⣬Ҳ�п�����һ��AcDbObject��
	//���owner�����ݿ⣬��ʾ����������������Ӳָ���ϵ�������Ƶģ�������ʵ��owner����ת��׶α���ȷ����
	//��ʱpOwn��ֵ����NULL����Ϊһ����־
	AcDbObject   *pOwn = AcDbObject::cast(pOwner);
	AcDbDatabase *pDb = AcDbDatabase::cast(pOwner);
	if (pDb == NULL)
		pDb = pOwn->database();

	//����һ��ͬ���͵Ķ���
	auto *pClone = (SampleCustEnt*)isA()->create();
	if (pClone != NULL)
		pClonedObject = pClone;
	else
		return Acad::eOutOfMemory;

	//���owner�Ǹ��������������֪����������ʲô���Ϳ���ֱ�����ø��ƶ����owner
	//����Ͱ�Դ�����owner���ø����ƶ�����ת��׶ν���ת���������Դ������Ŀ�����ownerһ����Ҳ����Ϊת��׶�Ҫ�õ���һ����־
	//Ҫע�������Դ�����ownerҲ����Ҫ�����Ƶ�Ŀ������ݿ���ģ�����ת��׶λ����
	AcDbBlockTableRecord *pBTR = NULL;
	if (pOwn != NULL)
		pBTR = AcDbBlockTableRecord::cast(pOwn);
	if (pBTR != NULL && isPrimary) {
		pBTR->appendAcDbEntity(pClone);
	}
	else {
		pDb->addAcDbObject(pClonedObject);
	}

	//ͨ��dwgOut��dwgIn�������ݵ����ƶ�����
	AcDbWblockCloneFiler filer;
	dwgOut(&filer);
	filer.seek(0L, AcDb::kSeekFromStart);
	pClone->dwgIn(&filer);

	//���Դ�����븴�ƶ���Id Map��ע��AcDbIdPair���캯�������һ������isOwnerXlated�����ƶ����owner�Ƿ���Ҫת��
	//�������������ͨ�������pOwn�Ƿ�Ϊ�����жϵ�
	idMap.assign(AcDbIdPair(objectId(), pClonedObject->objectId(),
		Adesk::kTrue,
		isPrim, (Adesk::Boolean)(pOwn != NULL)));
	pClonedObject->setOwnerId((pOwn != NULL) ?
		pOwn->objectId() : ownerId());

	//��deepcloneһ����Ҫ��ÿ�����ƶ������setAcDbObjectIdsInFlux()
	pClone->setAcDbObjectIdsInFlux();

	//�ݹ鸴�����е�Ӳ���к�Ӳָ��
	AcDbObjectId id;
	while (filer.getNextHardObject(id)) {
		AcDbObject *pSubObject;
		AcDbObject *pClonedSubObject;

		//ĳЩ����»�������õĶ���Ϊ�գ���Ҫ����
		if (id == NULL)
			continue;

		//������ö�����������һ�����ݿ⣬����Ҫ����
		acdbOpenAcDbObject(pSubObject, id, AcDb::kForRead);
		if (pSubObject->database() != database()) {
			pSubObject->close();
			continue;
		}

		//���������������������������ö����owner���Ͱ����ݿ���Ϊowner����ȥ
		//�����deepcloneһ��������isPrimary����Ҫ��Ϊfalse
		pClonedSubObject = NULL;
		if (pSubObject->ownerId() == objectId()) {
			pSubObject->wblockClone(pClone,
				pClonedSubObject,
				idMap, Adesk::kFalse);
		}
		else {
			pSubObject->wblockClone(
				pClone->database(),
				pClonedSubObject,
				idMap, Adesk::kFalse);
		}
		pSubObject->close();

		//�������ʧ�ܣ�pClonedSubObject���ǿ�ָ�룬��Ҫ���
		if (pClonedSubObject != NULL)
			pClonedSubObject->close();
	}

	//��deepcloneһ�������ƶ����ɵ�������close
	return Acad::eOk;
}
