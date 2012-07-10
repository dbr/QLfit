#include "fit_decode.hpp"
#include "fit_mesg_broadcaster.hpp"

#include <fstream>
#include <iostream>
#include <Foundation/Foundation.h>

namespace
{

typedef std::vector< std::pair<double, double> > latlng_list;


double semicircle_to_degree(FIT_SINT32 semi)
{
    // Value in 32-bit integer, in semicircles, where 2^31 semicircles are equal to 180 degrees
    // d = s * (180.0D / 2^31)

    return (double)semi * (180.0 / 2147483648.0);
}

class Listener : public fit::FileIdMesgListener, public fit::UserProfileMesgListener, public fit::RecordMesgListener
{
private:
    latlng_list points;

public:
    NSArray* get_array()
    {
        NSMutableArray *arr = [[NSMutableArray alloc] init];
        latlng_list::iterator it;
        for(it = points.begin(); it < points.end(); ++it)
        {
            //std::cerr << (*it).first << ", " << (*it).second << "\n";

            if((*it).first == 180 || (*it).second == 180)
            {
                // Probably invalid point
            } else {
                NSNumber *lat = [NSNumber numberWithDouble:(*it).first];
                NSNumber *lon = [NSNumber numberWithDouble:(*it).second];
                [arr addObject: [NSArray arrayWithObjects: lat, lon, nil]];
            }
        }

        return arr;
    }

    void OnMesg(fit::FileIdMesg& mesg)
    {
        printf("File ID:\n");
        if (mesg.GetType() == FIT_FILE_ACTIVITY)
            printf("   Activity file!\n");

        if (mesg.GetType() != FIT_FILE_INVALID)
            printf("   Type: %d\n", mesg.GetType());
        if (mesg.GetManufacturer() != FIT_MANUFACTURER_INVALID)
            printf("   Manufacturer: %d\n", mesg.GetManufacturer());
        if (mesg.GetProduct() != FIT_UINT16_INVALID)
            printf("   Product: %d\n", mesg.GetProduct());
        if (mesg.GetSerialNumber() != FIT_UINT32Z_INVALID)
            printf("   Serial Number: %d\n", static_cast<int>(mesg.GetSerialNumber()));
        if (mesg.GetNumber() != FIT_UINT16_INVALID)
            printf("   Number: %d\n", mesg.GetNumber());
    }

    void OnMesg(fit::RecordMesg& mesg)
    {
        //std::cerr << "Before " << mesg.GetPositionLat() << " and after: " << semicircle_to_degree(mesg.GetPositionLat()) << std::endl;
        //std::cerr << "Before " << mesg.GetPositionLong() << " and after: " << semicircle_to_degree(mesg.GetPositionLong()) << std::endl;
        //std::cerr << "Lat: " << semicircle_to_degree(mesg.GetPositionLat());
        //std::cerr << " Lon: " << semicircle_to_degree(mesg.GetPositionLong()) << std::endl;

        points.push_back(
            std::pair<float, float>(
                semicircle_to_degree(mesg.GetPositionLat()),
                semicircle_to_degree(mesg.GetPositionLong())));
    }

    void OnMesg(fit::UserProfileMesg& mesg)
    {
        printf("User profile:\n");
        if (mesg.GetFriendlyName() != FIT_WSTRING_INVALID)
            std::wcout << L"   Friendly Name: " << mesg.GetFriendlyName().c_str() << L"\n";
        if (mesg.GetGender() == FIT_GENDER_MALE)
            printf("   Gender: Male\n");
        if (mesg.GetGender() == FIT_GENDER_FEMALE)
            printf("   Gender: Female\n");
        if (mesg.GetAge() != FIT_UINT8_INVALID)
            printf("   Age [years]: %d\n", mesg.GetAge());
        if (mesg.GetWeight() != FIT_FLOAT32_INVALID)
            printf("   Weight [kg]: %0.2f\n", mesg.GetWeight());
    }
};

} // end anonymous namespace

extern "C"
{

    NSArray* get_points_from_fitfile(char* fname)
    {
        fit::MesgBroadcaster mesgBroadcaster;
        Listener listener;
        std::fstream file;

        file.open(fname, std::ios::in | std::ios::binary);

        if (!file.is_open())
        {
            printf("Error opening file %s\n", fname);
            return nil;
        }
        else
        {
            printf("Opened %s perfectly\n", fname);
        }


        fit::Decode decode;
        if (!decode.CheckIntegrity(file))
        {
            printf("FIT file integrity failed.\n");
            return nil;
        }

        mesgBroadcaster.AddListener((fit::FileIdMesgListener &)listener);
        mesgBroadcaster.AddListener((fit::UserProfileMesgListener &)listener);
        mesgBroadcaster.AddListener((fit::RecordMesgListener &)listener);

        try
        {
            mesgBroadcaster.Run(file);
        }
        catch (const fit::RuntimeException& e)
        {
            printf("Exception decoding file: %s\n", e.what());
            return nil;
        }

        return listener.get_array();

    }

}
