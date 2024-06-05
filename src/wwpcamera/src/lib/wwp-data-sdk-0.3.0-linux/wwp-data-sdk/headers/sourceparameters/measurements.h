#ifndef MEASUREMENTS_H
#define MEASUREMENTS_H

#include <vector>
#include <memory>
#include <iostream>

namespace wtl
{
/**
    * @brief Available Roi Types.
    */
enum class RoiType
{
    /** @brief One-point ROI */
    Point,
    /** @brief Rectangular-shaped ROI */
    Rectangle,
    /** @brief Straight-line ROI */
    Line,
    /** @brief Polygonal chain ROI */
    Polyline,
    /** @brief Polygon-shaped ROI */
    PolyArea,
    /** @brief Ecliptic ROI */
    Ellipse
};
/**
    * @brief Structure representing one ROI item in an image
    */
struct RoiStruct
{
    /**
     * @brief ROI type.
     */
    RoiType m_Type;
    /**
     * @brief ROI limit points, determine roi shape.
     */
    std::vector<std::pair<int, int>> m_Points;
    /**
     * @brief Custom parameters of roi on/off.
     */
    bool m_CustomParams = false;
    /**
     * @brief Custom emissivity of roi.
     */
    float m_Emissivity = 0.95;
    /**
     * @brief Custom reflected temperature of roi.
     */
    float m_ReflectedTemp = 20;
    /**
     * @brief Custom reflected temperature of roi.
     */
    float m_Distance = 1;
    /**
     * @brief Roi Color
     */
    uint8_t m_Color[3];

    std::string m_Name;

    /**
     * @brief Decide whether given pixes lays inside roi
     * @param x width coordinate.
     * @param y height coordinate.
     * @return true if pixel lays inside roi.
     */
    bool isInsideRoi(int x, int y) const;
};
/**
     * @brief Containter of all the measurements present in an image.
     * @details Provides interface for reading saved measurements as well as adding new measurements.
     */
class Measurements
{
    std::vector<std::shared_ptr<RoiStruct>> m_Rois;
public:
    /**
          * @brief Default class constructor.
          */
    Measurements() = default;
    /**
          * @brief Deleted copy contructor.
          */
    Measurements(const Measurements & x) = delete;
    /**
        * @brief Add new Roi to the image.
        * @param roi Roi structure that is to be added.
        */
    void addRoi(std::shared_ptr<RoiStruct> roi);
    /**
        * @brief Add new Roi to the image.
        * @param roi Roi structure that is to be added.
        */
    void addRoi(const RoiStruct & roi);
    /**
        * @brief Get all the rois currently saved to the image.
        * @return A Vector containing Roi Structures.
        */
    std::vector<std::shared_ptr<RoiStruct>> getRois() const;
    /**
        * @brief Roi Count.
        * @return Total number of rois currently added to the image.
        */
    int getRoiCount() const;
    /**
        * @brief Get Roi by index.
        * @return Roi stucture instance on the position specified by parameter idx.
        */
    const RoiStruct & getRoiAt(int idx) const;
    /**
    * @brief Get Roi by index.
    * @return Roi stucture pointer on the position specified by parameter idx.
    */
    std::shared_ptr<wtl::RoiStruct>  getRoiPtrAt(int idx) const;
    /**
    * @brief Delete roi specified by index.
    * @param idx Roi index
    * @return
    */
    bool deleteRoiAt(int idx);
    /**
             * @brief Delete roi given by pointer from list
             * @param roi Instance to be deleted from the list
             * @return
             */
    bool deleteRoiFromList(std::shared_ptr<RoiStruct> roi);
    /**
         * @brief clear all the measurements.
         */
    void clear();
};
}

#endif // MEASUREMENTS_H
