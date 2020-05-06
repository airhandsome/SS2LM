#ifndef _LIBSVM_H
#define _LIBSVM_H

#define LIBSVM_VERSION 318

#ifdef __cplusplus
extern "C" {
#endif

	extern int libsvm_version;

	struct svm_node   //向量点，比如1：0.002 2：0.001
	{
		int index;
		double value;
	};

	struct svm_problem
	{
		int l;     //样本总数
		double *y;	//正类负类
		struct svm_node **x;	//具体的X的点相当于svm_node[]
	};

	enum { C_SVC, NU_SVC, ONE_CLASS, EPSILON_SVR, NU_SVR, SVDD, R2, R2q, SS2LM };	/* svm_type */
	enum { LINEAR, POLY, RBF, SIGMOID, PRECOMPUTED }; /* kernel_type */

	struct svm_parameter
	{
		int svm_type;
		int kernel_type;
		int degree;	/* for poly */
		double gamma;	/* for poly/rbf/sigmoid */
		double coef0;	/* for poly/sigmoid */

		/* these are for training only */
		double cache_size; /* in MB */
		double eps;	/* stopping criteria */
		double C;	/* for C_SVC, EPSILON_SVR and NU_SVR */
		int nr_weight;		/* for C_SVC */
		int *weight_label;	/* for C_SVC */
		double* weight;		/* for C_SVC */
		double nu;	/* for NU_SVC, ONE_CLASS, and NU_SVR */
		double p;	/* for EPSILON_SVR */
		int shrinking;	/* use the shrinking heuristics */
		int probability; /* do probability estimates */
		double ro; /*for SS2LM*/
		double v, v1, v2;/*for SS2LM*/
		double sigma;/*for SS2LM, outter/inner*/
		int m1, m2;//m1 is the positive number, m2 is the negative number

	};

	//
	// svm_model
	//
	struct svm_model
	{
		struct svm_parameter param;	/* parameter */ //训练参数
		int nr_class;		/* number of classes, = 2 in regression/one class svm 取值为1或者2，表示一类分类器或者二类分类器*/
		int l;			/* total #SV 总的向量数 */
		struct svm_node **SV;		/* SVs (SV[l]) */
		double **sv_coef;	/* coefficients for SVs in decision functions (sv_coef[k-1][l]) */
		double *rho;		/* constants in decision functions (rho[k*(k-1)/2]) */
		double *probA;		/* pariwise probability information */
		double *probB;
		int *sv_indices;        /* sv_indices[0,...,nSV-1] are values in [1,...,num_traning_data] to indicate SVs in the training set */
		double c_square;  //for ss2lm
		double p1;  //for ss2lm
		double p2;   //for ss2lm
		double r_square; //for ss2lm
		/* for classification only */

		int *label;		/* label of each class (label[k]) */
		int *nSV;		/* number of SVs for each class (nSV[k]) */
		/* nSV[0] + nSV[1] + ... + nSV[k-1] = l */
		/* XXX */
		int free_sv;		/* 1 if svm_model is created by svm_load_model*/
		/* 0 if svm_model is created by svm_train */
	};
	//训练数据
	struct svm_model *svm_train(const struct svm_problem *prob, const struct svm_parameter *param);
	//交叉验证
	void svm_cross_validation(const struct svm_problem *prob, const struct svm_parameter *param, int nr_fold, double *target);
	//保存训练好的模型到文件
	int svm_save_model(const char *model_file_name, const struct svm_model *model);
	//从文件中把训练好的模型到内存中
	struct svm_model *svm_load_model(const char *model_file_name);
	//获取数据集的SVM类型
	int svm_get_svm_type(const struct svm_model *model);
	//获取数据集的类别
	int svm_get_nr_class(const struct svm_model *model);
	//获取数据集的类别标号
	void svm_get_labels(const struct svm_model *model, int *label);
	void svm_get_sv_indices(const struct svm_model *model, int *sv_indices);
	int svm_get_nr_sv(const struct svm_model *model);
	double svm_get_svr_probability(const struct svm_model *model);
	//用训练好的模型预报样本的值，输出结果保留到数组中。（并非接口函数）
	double svm_predict_values(const struct svm_model *model, const struct svm_node *x, double* dec_values);
	//预报某一样本的值
	double svm_predict(const struct svm_model *model, const struct svm_node *x);
	double svm_predict_probability(const struct svm_model *model, const struct svm_node *x, double* prob_estimates);
	//释放模型资源
	void svm_free_model_content(struct svm_model *model_ptr);
	void svm_free_and_destroy_model(struct svm_model **model_ptr_ptr);
	void svm_destroy_param(struct svm_parameter *param);
	//检查输入参数保证后面的训练正常运行
	const char *svm_check_parameter(const struct svm_problem *prob, const struct svm_parameter *param);
	int svm_check_probability_model(const struct svm_model *model);

	void svm_set_print_string_function(void(*print_func)(const char *));

#ifdef __cplusplus
}
#endif

#endif /* _LIBSVM_H */
