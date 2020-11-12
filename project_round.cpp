#include <boost/program_options.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/filesystem.hpp>

#include <pcl/point_cloud.h>
#include <pcl/visualization/cloud_viewer.h>
#include <pcl/io/pcd_io.h>

int main (int argc, char** argv)
{
    std::string input_pcd;
    namespace po = boost::program_options;
    namespace fs = boost::filesystem;

    po::options_description desc("Allowed options");
    po::variables_map vm;



    try
    {
        desc.add_options()
            ("help", "produce help message")
            ("pcl", po::value<std::string>(&input_pcd)->required(), "pcd file name");
        
        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm);    

    }
    catch(const boost::program_options::required_option & e) 
    {
        if (vm.count("help")) 
        {
            std::cout << desc << std::endl;
            return 1;
        } else {
            std::cout << desc << std::endl;
            throw e;
        }
    }

    if (vm.count("help"))
    {
        std::cout << desc << std::endl;
        return 1;
    }

    boost::filesystem::path pcl_path (input_pcd);
    boost::filesystem::path root_dir = pcl_path.parent_path();
    boost::filesystem::path file_body = pcl_path.leaf();
    file_body.replace_extension();

    std::cout << "root directory: " << root_dir.string() << std::endl;
    std::cout << "file body: " << file_body.string() << std::endl;

    std::string outputFolder = root_dir.string() + "/" + file_body.string() + "_round";

    std::cout << "output directory: "  << outputFolder << std::endl;
    fs::create_directory(outputFolder);

    double targPos[] = { 0, -3, 30.0 };
    double roundRadius = 3;
    double animAngle = 0;
    int animCount = 0;

    pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZRGB>());
    pcl::io::loadPCDFile (pcl_path.string(), *cloud);

    pcl::visualization::PCLVisualizer::Ptr viewer(new pcl::visualization::PCLVisualizer ("3D Viewer"));
    //viewer->setCameraPosition(0, 0, 0, 0, 0, 1, 0, 1, 0, 0);
    viewer->setCameraFieldOfView(M_PI * 90 / 180.0);
    viewer->addPointCloud<pcl::PointXYZRGB>(cloud, "point cloud");
    viewer->setShowFPS (false); 

    while (!viewer->wasStopped())
    {
        viewer->setCameraPosition(2.0 * roundRadius*cos(1.0*animAngle), roundRadius*sin(1.0*animAngle)-4, 0, targPos[0], targPos[1], targPos[2], 0, -1, 0, 0);
        if (animAngle < 6.28)viewer->saveScreenshot(outputFolder + "/animation_segm" + std::to_string(animCount) + ".png");
        else break;
        viewer->spinOnce();
        animAngle += 0.02;
        animCount++;
    }
}