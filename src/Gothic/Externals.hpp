namespace GOTHIC_NAMESPACE {

    // func void VobTree_Remove(var string vobName) {};
	int VobTree_Remove()
	{
		zCParser* par = parser;
		zSTRING vobName;

		par->GetParameter(vobName);

		zVobTree::Remove(vobName);

		return 0;
	}

	// func void VobTree_Insert(var string filePath) {};
	int VobTree_Insert() {
		zCParser* par = parser;
		zSTRING path;

		par->GetParameter(path);

		zVobTree::Insert(path);

		return 0;
	}

	// func void VobTree_InsertParent(var string filePath, var string vobName) {};
	int VobTree_InsertParent() {
		zCParser* par = parser;
		zSTRING parentName;
		zSTRING path;

		par->GetParameter(parentName);
		par->GetParameter(path);

		zVobTree::InsertParent(path, parentName);

		return 0;
	}


    void DefineExternals()
    {
        parser->DefineExternal("VobTree_Remove", VobTree_Remove, zPAR_TYPE_VOID, zPAR_TYPE_STRING, zPAR_TYPE_VOID);
		parser->DefineExternal("VobTree_Insert", VobTree_Insert, zPAR_TYPE_VOID, zPAR_TYPE_STRING, zPAR_TYPE_VOID);
        parser->DefineExternal("VobTree_InsertParent", VobTree_InsertParent, zPAR_TYPE_VOID, zPAR_TYPE_STRING, zPAR_TYPE_STRING, zPAR_TYPE_VOID);
    }
}
