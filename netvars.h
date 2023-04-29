#pragma once

typedef enum
{
	DPT_Int = 0,
	DPT_Float,
	DPT_Vector,
	DPT_VectorXY, // Only encodes the XY of a vector, ignores Z
	DPT_String,
	DPT_Array,	// An array of the base types (can't be of datatables).
	DPT_DataTable,
	DPT_Int64,
	DPT_NUMSendPropTypes
} SendPropType;

class RecvTable;
class DVariant;
class RecvProp;
class RecvTable;
class ClientClass;
class CRecvProxyData;

typedef void (*RecvVarProxyFn)(const CRecvProxyData* pData, void* pStruct, void* pOut);
typedef void (*ArrayLengthRecvProxyFn)(void* pStruct, int objectID, int currentArrayLength);
typedef void (*DataTableRecvVarProxyFn)(const RecvProp* pProp, void** pOut, void* pData, int objectID);

class CRecvDecoder
{
public:

	RecvTable* m_pTable;
};

class DVariant
{
public:

	DVariant() { m_Type = DPT_Float; }

	explicit DVariant(float val) { m_Type = DPT_Float; m_Float = val; }

	union
	{
		float	m_Float;
		long	m_Int;
		char* m_pString;
		void* m_pData;	// For DataTables.
		float	m_Vector[3];
		int64_t	m_Int64;
	};
	SendPropType	m_Type;
};

class CRecvProxyData
{
public:
	const RecvProp* m_pRecvProp;		// The property it's receiving.

	DVariant		m_Value;			// The value given to you to store.

	int				m_iElement;			// Which array element you're getting.

	int				m_ObjectID;			// The object being referred to.
};

class RecvProp
{
public:

	char*						m_pVarName;
	SendPropType				m_RecvType;
	int							m_Flags;
	int							m_StringBufferSize;
	bool						m_bInsideArray;
	const void*					m_pExtraData;
	RecvProp*					m_pArrayProp;
	ArrayLengthRecvProxyFn		m_ArrayLengthProxy;
	RecvVarProxyFn				m_ProxyFn;
	DataTableRecvVarProxyFn		m_DataTableProxyFn;
	RecvTable*					m_pDataTable;
	int							m_Offset;
	int							m_ElementStride;
	int							m_nElements;
	const char*					m_pParentArrayPropName;

};

class RecvTable
{
public:

	RecvProp*		m_pProps; // array of props
	int				m_nProps;
	// The decoder. NOTE: this covers each RecvTable AND all its children (ie: its children
	// will have their own decoders that include props for all their children).
	CRecvDecoder*	m_pDecoder;
	char*			m_pNetTableName;	// The name matched between client and server.
	bool			m_bInitialized;
	bool			m_bInMainList;
};

class ClientClass
{
public:

	void*				m_pCreateFn;
	void*				m_pCreateEventFn;	// Only called for event objects.
	char*				m_pNetworkName;
	RecvTable*			m_pRecvTable;		
	ClientClass*		m_pNext;			// singly linked list
	int					m_ClassID;			// Managed by the engine.
	const char*			m_pMapClassname;
};

class Netvar
{
private:

	RecvTable* m_table;
	RecvProp* m_prop;

public:

	Netvar();
	Netvar(RecvTable* table, RecvProp* prop);

	operator bool();

	const char*		get_table_name();
	const char*		get_prop_name();
	int				get_offset();
};

class NetvarManager
{
private:

	std::vector<Netvar*> m_vars;

public:

	NetvarManager();
	NetvarManager(ClientClass* cl);

	operator bool();

	void dump(RecvTable* table);

	Netvar* get(const char* table_name, const char* prop_name);
};