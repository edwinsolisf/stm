#ifndef stm_simplex_noise_h
#define stm_simplex_noise_h

#include "matrix.h"
#include "vector.h"
#include "dynamic_matrix.h"
#include "dynamic_vector.h"

#include <functional>

namespace stm
{
	template<uint32_t dimensions>
	class simplex_noise
	{
	public:
		simplex_noise();
		simplex_noise(uint32_t seed, bool discontinuity = true, bool fast_floor = true, 
					  std::function<uint32_t(uint32_t)> hash_function = default_hash,
					  std::function<float(float)> normalize_function = default_normalizer);
		simplex_noise(uint32_t seed, float discontinuity_factor = 0.6f, bool fast_floor = true, 
					  std::function<stm::dynamic_vector<float>(int32_t, uint32_t, std::function<uint32_t(uint32_t)>)> 
					  gradient_generator_function = default_gradient_generator,
					  std::function<float(float)> normalize_function = default_normalizer);

		float Noise(const stm::vector<float, dimensions>& coordinates) const;
		stm::dynamic_vector<float> GenNoiseMap(const stm::vector<uint32_t, dimensions>& map_dimensions, float scale = 1.0f) const;
		
	private:
		uint32_t _seed;
		float _discontinuity_factor;
		std::function<float(float)> _floor;
		std::function<uint32_t(uint32_t)> _hash;
		std::function<float(float)> _normalize_scale;
		std::function<stm::dynamic_vector<float>(int32_t, uint32_t, std::function<uint32_t(uint32_t)>)> _gradient_generator;
		stm::dynamic_vector<uint32_t> _permutations;

		static stm::dynamic_vector<uint32_t> GenRandomPermutations(uint32_t size);
		static stm::dynamic_vector<uint32_t> GenPermutations(uint32_t size, uint32_t seed);

		static float default_floor(float);
		static uint32_t default_hash(uint32_t);
		static float default_normalizer(float discontinuity_factor);
		static stm::dynamic_vector<float> default_gradient_generator(int32_t, uint32_t, 
																	 std::function<uint32_t(uint32_t)> hash = default_hash);

		stm::vector<uint32_t, dimensions> GetVertexIndicesOrder(const stm::vector<float, dimensions>& internal_coordinates) const;
		float GetVertexNoiseValue(const stm::vector<float, dimensions>& vertex, float discontinuity_factor,
								  const stm::vector<uint32_t, dimensions>& indices, const stm::vector<int32_t, dimensions>& base_coordinate) const;
		float GradientDotProduct(int32_t permutation, const stm::vector<float, dimensions> vertex) const;
		int32_t PermutationIndices(const stm::vector<uint32_t, dimensions> indices, const stm::vector<int32_t, dimensions>& base_coordinate) const;
		
		static int32_t CountBits(int32_t val);
		static int32_t GetEdgeDirection(int32_t original, uint32_t dim, std::function<uint32_t(uint32_t)> hash = default_hash);
		static bool GetSignDirection(int32_t original, uint32_t dim);
	};
}

#include "simplex_noise.ipp"

#endif