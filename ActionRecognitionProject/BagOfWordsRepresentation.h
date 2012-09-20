#ifndef BAGOFWORDSREPRESENTATION_H
#define BAGOFWORDSREPRESENTATION_H

#include <opencv2\core\core.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <fstream>
#include <qstringlist.h>
#include <qstring.h>

using namespace std;

enum matchType {BF_L2, BF_L1, KNN, USER};

class BagOfWordsFeature
{
public:
	BagOfWordsFeature();
	BagOfWordsFeature(const BagOfWordsFeature &b);
	BagOfWordsFeature &operator= (const BagOfWordsFeature &b) {return *this;};

	cv::Mat bag_of_words;
	int *_ft;
	unsigned int number_of_words; // in the bag of words.

	cv::DescriptorMatcher *matcher; // for matching vectors to BoWs
	matchType matcher_type;

};

class BagOfWordsRepresentation
{
public:
	BagOfWordsRepresentation(QStringList &qsl, int num_clust, int ftr_dim, int num_people);
	void computeBagOfWords();
	void setMotionDescriptor(unsigned int size, bool binary = false);
	void setAppearanceDescriptor(unsigned int size, bool binary = false);

private:
	void loadClusters();
	cv::Mat buildHistogram(QString &file);
	float standardEuclideanDistance(cv::Mat &a, cv::Mat &b) const;
	void findBestMatch(cv::Mat &feature_vector, cv::Mat &clusters, int &best_cluster_index, float &best_cluster_score);
	void findBestMatchFREAKAndOpticalFlow(cv::Mat &feature_vector, cv::Mat &clusters, int &best_cluster_index, float &best_cluster_score, ofstream &file);
	void findBestMatchFREAKAndFrameDifference(cv::Mat &feature_vector, cv::Mat &clusters, int &best_cluster_index, float &best_cluster_score);
	unsigned int hammingDistance(cv::Mat &a, cv::Mat &b);

	void normalizeClusters();
	void normalizeMotionOfFeature(cv::Mat &ftr);
	void normalizeAppearanceOfFeature(cv::Mat &ftr);

	QStringList files;
	const int NUMBER_OF_CLUSTERS;
	const int FEATURE_DIMENSIONALITY;
	const int NUMBER_OF_PEOPLE;
	cv::Mat *clusters;
	enum class_action {BOXING, HANDCLAPPING, HANDWAVING, JOGGING, RUNNING, WALKING};

	unsigned int motion_descriptor_size;
	unsigned int appearance_descriptor_size;
	bool motion_is_binary;
	bool appearance_is_binary;
};
#endif