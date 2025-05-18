namespace GOTHIC_NAMESPACE {

    //remove vobtree by parent name
	int VobTree_Remove()
	{
        static NH::Logger* log = NH::CreateLogger("VobTree_Remove");
		zCParser* par = parser;
		zSTRING vobName;

		par->GetParameter(vobName);

		if (!IsWorldReadyOrLoaded(false)) return 0;

		if (vobName.Length() > 0)
		{
			zCVob* pVob = ogame->GetWorld()->SearchVobByName(vobName);

			if (pVob)
			{
				zCTree<zCVob>* tree = pVob->globalVobTreeNode;
				GetChildrenPFX(tree, pVob, pVob);
				ogame->GetWorld()->RemoveVobSubtree(pVob);
                log->Info("Vobtree removed from '{0}'", vobName.ToChar());
			}
            else
            {
                log->Warning("Vob '{0}' not found", vobName.ToChar());
            }

		}
		return 0;
	}

	//insert vobtree globally by filename
	int VobTree_Insert() {
        static NH::Logger* log = NH::CreateLogger("VobTree_Insert");
		zCParser* par = parser;
		zSTRING path;

		par->GetParameter(path);

		if (InsertVobTree(path, "")) {
            log->Info("Vobtree '{0}' inserted", path.ToChar());
        } 
        else {
            log->Warning("Cannot insert '{0}'", path.ToChar());
        }

		return 0;
	}

	//insert vobtree by filename into a vob with name 
	int VobTree_InsertParent() {
        static NH::Logger* log = NH::CreateLogger("VobTree_InsertParent");
		zCParser* par = parser;

		zSTRING parentName;
		zSTRING path;


		par->GetParameter(parentName);
		par->GetParameter(path);

		if (InsertVobTree(path, parentName)) {
            log->Info("Vobtree '{0}' inserted into '{1}'", path.ToChar(), parentName.ToChar());
        }
        else {
            log->Warning("Cannot insert '{0}' into '{1}'", path.ToChar(), parentName.ToChar());
        }

		return 0;
	}


    void DefineExternals()
    {
        parser->DefineExternal("VobTree_Remove", VobTree_Remove, zPAR_TYPE_VOID, zPAR_TYPE_STRING, zPAR_TYPE_VOID);
		parser->DefineExternal("VobTree_Insert", VobTree_Insert, zPAR_TYPE_VOID, zPAR_TYPE_STRING, zPAR_TYPE_VOID);
        parser->DefineExternal("VobTree_InsertParent", VobTree_InsertParent, zPAR_TYPE_VOID, zPAR_TYPE_STRING, zPAR_TYPE_STRING, zPAR_TYPE_VOID);
    }
}
