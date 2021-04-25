#include "doctorprofiledata.h"
#include "packer.h"


SubscriptionData::SubscriptionData(DoctorProfileData data, int spec_id, int group_id, int package_id)
{
    foreach(auto spec, data.specializations)
    {
        if(spec.id == spec_id)
        {
            setSpecializations(spec);
            foreach(auto group, spec.groups)
            {
                if(group.id == group_id)
                {
                    setGroup(group);
                    foreach(auto package, group.packages)
                    {
                        if(package.id == package_id)
                            setPackage(package);
                    }
                }
            }
        }
    }
}

void SubscriptionData::setSpecializations(Specialization spec)
{
    specialization_id = spec.id;
    specialization_name = spec.name;
    specialization_info = spec.info;
}

void SubscriptionData::setGroup(ServicePackageGroup group)
{
    group_id = group.id;
    type_name = GlobalData::strings::subscriptionTypeNames.find(group.subscriptionType).value();
    type_interval = GlobalData::strings::subscriptionTypeValue.find(group.subscriptionType).value();
}

void SubscriptionData::setPackage(ServicePackage package)
{
    package_id = package.id;
    cost = package.cost;
    valuta = package.valuta;
    time = package.consultationTime;
}


DoctorProfileData::DoctorProfileData(const DoctorProfileData &data)
{
    operator=(data);
}

void DoctorProfileData::operator=(const DoctorProfileData &data)
{
    id = data.id;
    base = data.base;
    education = data.education;
    job = data.job;
    workTime_begin = data.workTime_begin;
    workTime_end = data.workTime_end;
    replyInterval = data.replyInterval;

    achievements = data.achievements;
    comments = data.comments;
    specializations = data.specializations;
}
