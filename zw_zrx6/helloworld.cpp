#include "pch.h"
#include <vector>
#include "SampleCustEnt.h"
using namespace std;

void helloworld()
{
	auto pDb = acdbHostApplicationServices()->workingDatabase();
	AcDbBlockTable* pBT = nullptr;
	pDb->getBlockTable(pBT, AcDb::kForRead);//�����ݿ��ȡ���
	if (pBT)//�ж��Ƿ�ɹ�
	{
		AcDbBlockTableRecord* pBTR = nullptr;
		//ACDB_MODEL_SPACE = "*Model_Space"
		pBT->getAt(ACDB_MODEL_SPACE, pBTR, AcDb::kForWrite);//�ӿ���ȡģ�Ϳռ�Ŀ���¼ 
		pBT->close();//��������Ϲر�
		if (pBTR)
		{

			ads_name ori_en1;
			ads_point pt1, pt2;
			AcDbObjectId id1;
			acedEntSel(_T("\nѡ��һ��ʵ��: "), ori_en1, pt1);

			AcDbPolyline* pEnt;
			acdbGetObjectId(id1, ori_en1);
			acdbOpenAcDbEntity((AcDbEntity*&)pEnt, id1, AcDb::kForRead);
			if(pEnt)
			{
				SampleCustEnt* ent = new SampleCustEnt;

				AcGePoint3d oript, midpt;
				pEnt->getPointAt(0, oript);
				pEnt->getPointAt(2, midpt);
				ent->setstartpt(oript);
				ent->setendpt(midpt);

				for (int i = 0; i < pEnt->numVerts(); i++)
				{
					AcGePoint3d pti;
					pEnt->getPointAt(i, pti);
					ent->pts.push_back(pti);
				}


				ads_real r;				acedGetReal(_T("\n�������ű���"), &r);				ent->setzoom(r);
				ads_real ang;				acedGetAngle(NULL, _T("\n����Ƕȣ�"), &ang);				ent->setangle(ang);

				AcGePoint3d ptt;
				ptt = ent->getPointAt(0);
				acedGetPoint(asDblArray(ptt), _T("�����յ�: "), pt2);
				ent->settargetpt(asPnt3d(pt2));

				AcDbExtents ext;
				pEnt->getGeomExtents(ext);
				ads_name ss;
				acedSSGet(_T("C"), asDblArray(ext.minPoint()), asDblArray(ext.maxPoint()), NULL, ss);
				Adesk::Int32 len = 0;
				acedSSLength(ss, &len);
				for (auto i = 0; i < len; i++) {
					ads_name en;
					acedSSName(ss, i, en);
					AcDbObjectId objId;
					acdbGetObjectId(objId, en);
					ent->m_idsForDisp.push_back(objId);
				}
				acedSSFree(ss);

				for (int i = 0; i < ent->m_idsForDisp.size(); i++)
				{
					ads_printf(_T("1"));
				}

				AcDbObjectId enid;
				pBTR->appendZcDbEntity(enid, ent);
				ads_printf(_T("done"));

				ent->close();
				pEnt->close();
			}



			pBT->close();

			pBTR->close();


		}
	}

}

void test()
{
	auto pDb = acdbHostApplicationServices()->workingDatabase();
	AcDbBlockTable* pBT = nullptr;
	pDb->getBlockTable(pBT, AcDb::kForRead);//�����ݿ��ȡ���
	if (pBT)//�ж��Ƿ�ɹ�
	{
		AcDbBlockTableRecord* pBTR = nullptr;
		//ACDB_MODEL_SPACE = "*Model_Space"
		pBT->getAt(ACDB_MODEL_SPACE, pBTR, AcDb::kForWrite);//�ӿ���ȡģ�Ϳռ�Ŀ���¼ 
		pBT->close();//��������Ϲر�
		if (pBTR)
		{

			//pGeom->popModelTransform();
			pBT->close();

			pBTR->close();


		}
	}

}

int showhello(struct resbuf *rb)
{
	ads_printf(_T("hello"));
	ads_retvoid();
	return RTNORM;
}

int showhellocmd(struct resbuf *rb)
{
	ads_printf(_T("hello"));
	ads_retvoid();
	return RTNORM;
}
