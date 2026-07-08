template<typename T>
class CsvRepository :
    public MemoryRepository<T>
{
public:

    bool load(
        const std::string& filename);

    bool save(
        const std::string& filename) const;
};
std::ifstream file(filename);

if(!file)
    return false;

this->clear();

std::string line;

while(std::getline(file,line))
{
    if(line.empty())
        continue;

    this->insert(
        CsvSerializer<T>::deserialize(
            line
        )
    );
}

return true;
std::ofstream file(filename);

if(!file)
    return false;

for(size_t i=0;i<this->size();++i)
{
    file
        << CsvSerializer<T>::serialize(
            this->at(i)
        )
        << '\n';
}

return true;
