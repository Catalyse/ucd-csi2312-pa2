#include <vector>
#include <sstream>
#include <iomanip>
#include <cmath>
#include "Cluster.h"
#include "KMeans.h"

using namespace std;

namespace Clustering
{
    double KMeans::SCORE_DIFF_THRESHOLD = 0.005;

    KMeans::~KMeans(){}

    // KMeans member functions

    int get_closest_centroid(Cluster ** clstr, int k, const PointPtr pointPtr)
    {
        int n = 0;
        int distA, distB;
        distA = pointPtr->distanceTo(clstr[0]->getCentroid());

        for (int i = 0; i < k; i++)
        {
            distB = pointPtr->distanceTo(clstr[i]->getCentroid());
            if (distB < distA)
            {
                n = i;
                distA = distB;
            }
        }
        return n;
    }

    void KMeans::computeClusteringScore(){

        double cDistOuter_sum = 0;
        double cDistInner_sum = 0;
        double cEdgeOuter_sum = 0;
        double cEdgeInner_sum = 0;

        double * cDistOuter = new double[this->__k];
        double * cDistInner = new double[this->__k];
        double * cEdgeOuter = new double[this->__k];
        double * cEdgeInner = new double[this->__k];

        double betaCV=0;

        for (int i = 0; i < this->__k; i++)
        {
            cDistOuter[i] = this->__clusters[i]->intraClusterDistance();
            cEdgeOuter[i] = this->__clusters[i]->getClusterEdges();
            for (int j = 0; j < this->__k; j++)
            {
                if (i != j)
                {
                    cDistInner[i] += interClusterDistance(*this->__clusters[i], *this->__clusters[j]);
                    cEdgeInner[i] += interClusterEdges(*this->__clusters[i], *this->__clusters[j]);
                }
            }
        }
        for (int i = 0; i < this->__k; i++)
        {
            cDistOuter_sum += cDistOuter[i];
            cDistInner_sum += cDistInner[i];
            cEdgeOuter_sum += cEdgeOuter[i];
            cEdgeInner_sum += cEdgeInner[i];
        }
        cDistOuter_sum /= 2;
        if (cDistOuter_sum == 0)
        {
            betaCV = 0;
        }
        else if (cEdgeInner_sum == 0)
        {
            betaCV = std::numeric_limits<double>::max();
        }
        else
        {
            betaCV = (cDistOuter_sum/cEdgeOuter_sum) / (cDistInner_sum/cEdgeInner_sum);
        }
        this->__score = betaCV;
    }



    void KMeans::run()
    {
        double score1, score2, scoreDiff;
        int closestCentroid = 0;
        score1 = this->__score;
        scoreDiff = KMeans::SCORE_DIFF_THRESHOLD + 1;
        while (scoreDiff > KMeans::SCORE_DIFF_THRESHOLD)
        {
            // loop through all __clusters
            for (int i = 0; i < this->__k; i++)
            {
                // loop through all __points in cluster i
                // Loop through every point in cluster i
                for (int j = 0; j < this->__clusters[i]->getSize(); j++)
                {
                    PointPtr ptr = (*this->__clusters[i])[j];
                    // determine the closest centroid
                    closestCentroid = get_closest_centroid(this->__clusters, this->__k, ptr);
                    // if centroid is not of current cluster
                    if (closestCentroid != i )
                    {
                        Cluster::Move m(ptr, this->__clusters[i], this->__clusters[closestCentroid]);
                        m.perform();
                    }
                }
            }
            // loop through all __clusters
            for (int i = 0; i < this->__k; i++)
            {
                if (!this->__clusters[i]->isCentroidValid())
                {
                    this->__clusters[i]->computeCentroid();
                }
            }
            this->computeClusteringScore();
            score2 = this->__score;
            scoreDiff = abs(score1 - score2);
            score1 = score2;
        }
    }


    Cluster & KMeans::operator[](unsigned int u)
    {
        return *this->__clusters[u];
    }

    const Cluster & KMeans::operator[](unsigned int u) const
    {
        return *this->__clusters[u];
    }

    ostream &operator<<(ostream &stream, const KMeans &kmeans)
    {
        for (int i = 0; i < kmeans.__k; i++)
        {
            stream << *(kmeans).__clusters[i];
        }
        return stream;
    }
}