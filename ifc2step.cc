#include <ifcpp/IFC4/include/IfcBuildingStorey.h>
#include <ifcpp/IFC4/include/IfcGloballyUniqueId.h>
#include <ifcpp/model/BuildingModel.h>
#include <ifcpp/reader/ReaderSTEP.h>
#include <ifcpp/writer/WriterSTEP.h>
#include <codecvt>
#include <locale>
#include <fstream>

template<class I, class E, class S>
struct codecvt : std::codecvt<I, E, S>
  {
    ~codecvt(){ }
  };
  
std::wstring char_ptr_to_wstring(char *arg)
  {
    std::wstring_convert< codecvt<wchar_t,char,std::mbstate_t> > converter;
    std::wstring retval(converter.from_bytes(arg));
    return retval;
  }

int main(int argc, char* argv[])
  {
    // create an IFC model and a reader for IFC files in STEP format:
    shared_ptr<BuildingModel> ifc_model(new BuildingModel());
    shared_ptr<ReaderSTEP> step_reader(new ReaderSTEP());

    if(argc>1)
      {
	// read file name:
	const std::wstring fileName= char_ptr_to_wstring(argv[1]);
	// load the model:
	step_reader->loadModelFromFile(fileName, ifc_model);
	
	// get a map of all loaded IFC entities:
	const std::map<int, shared_ptr<BuildingEntity> >& map_entities = ifc_model->getMapIfcEntities();

	for(auto it : map_entities)
	  {
	    shared_ptr<BuildingEntity> entity = it.second;

	    // check for certain type of the entity:
	    shared_ptr<IfcBuildingStorey> ifc_storey = dynamic_pointer_cast<IfcBuildingStorey>(entity);
	    if(ifc_storey)
	      {
		    // access attributes:
		    if (ifc_storey->m_GlobalId)
		    {
			    std::wcout << L"found IfcBuildingStorey entity with GUID: " << ifc_storey->m_GlobalId->m_value << std::endl;
		    }
	      }
	  }
	
	std::stringstream stream;
	shared_ptr<WriterSTEP> step_writer(new WriterSTEP());
	step_writer->writeModelToStream(stream, ifc_model);
	ifc_model->clearIfcModel();
        std::ofstream ofs("./pp.stp", std::ofstream::out);
	ofs << stream.str().c_str();
	ofs.close();

      }
    else
      std::cerr << "syntax: " << argv[0] << " input_file" << std::endl;
	
  }
